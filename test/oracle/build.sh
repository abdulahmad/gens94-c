#!/usr/bin/env bash
# Build out/lockstep/gens94-lockstep: gens94-c's game code (game/, unchanged, with its own headers)
# in ninety-four's lockstep host (native/: its HAL with the port-access counters, its lockstep
# player and run loop), so the game code here is checked against the cartridge at every vblank
# (plan step E3; test/oracle/lockstep.py runs it). Nothing in game/ or platform/ changes.
#
# Needs a ninety-four checkout (NHL94, default ../NHL94Genesis-C-Port) set up for its own lockstep
# (its tools/e2_setup.sh, then make vectors): its pulseman build, native/ and out/vectors.
#
# What is ninety-four's here, not gens94-c's: the HAL (platform/hal.c is a cut of the same file,
# without the counters lockstep needs) and the run loop. The glue (lockstep_glue.c) gives the
# host what gens94-c cut: the cartridge's roster set and art (the only one gens94-c plays) and the
# wide view's resume (off). restart_at is wrapped so the player hears of its longjmp, as
# ninety-four's own restart_at tells it (run68k_unwind).
set -euo pipefail
HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
NHL94="$(cd "${NHL94:-$ROOT/../NHL94Genesis-C-Port}" && pwd)"
OUT="$ROOT/out/lockstep"
CC="${CC:-gcc}"
MDRT="$NHL94/ext/pulseman"
[ -f "$MDRT/build/release/libmdrt.a" ] || make -C "$MDRT" MODE=release B=build/release sdl >/dev/null
[ -f "$NHL94/build/build_id.h" ] || make -C "$NHL94" build/build_id.h >/dev/null
SDLCF="$(pkg-config --cflags sdl2)"
WARN="-Wall -Wextra -Wshadow -Wstrict-prototypes -Wmissing-prototypes -Wno-unused-parameter -Werror"
GAMECF="-std=gnu11 $WARN -O2 -I$ROOT/game -I$MDRT/include -finstrument-functions"
HOSTCF="-std=gnu11 $WARN -O2 -I$NHL94/src -I$NHL94/native -I$NHL94/build -I$MDRT/include $SDLCF"
mkdir -p "$OUT/obj"
objs=()
for f in "$ROOT"/game/*/*.c; do
  o="$OUT/obj/game_$(basename "$f" .c).o"; objs+=("$o")
  [ "$o" -nt "$f" ] || $CC $GAMECF -c "$f" -o "$o" &
done
for f in "$NHL94"/native/*.c "$NHL94/src/rules.c" "$HERE/lockstep_glue.c"; do
  o="$OUT/obj/host_$(basename "$(dirname "$f")")_$(basename "$f" .c).o"; objs+=("$o")
  [ "$o" -nt "$f" ] || $CC $HOSTCF -c "$f" -o "$o" &
done
wait
$CC -o "$OUT/gens94-lockstep" "${objs[@]}" -Wl,--wrap=restart_at \
  "$MDRT/build/release/libmdrt_sdl2.a" "$MDRT/build/release/libmdrt.a" \
  $(pkg-config --libs sdl2 | sed 's/-mwindows//') -lm -lstdc++
echo "built $OUT/gens94-lockstep (game/ from gens94-c $(git -C "$ROOT" rev-parse --short HEAD), host from ninety-four $(git -C "$NHL94" rev-parse --short HEAD))"
