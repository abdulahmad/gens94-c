# NHL '94 in C

> **Credits:** built on [NHL94Genesis](https://github.com/abdulahmad/NHL94Genesis) by abdulahmad, with chaos, StaticEck, McMarkis (Mhopkinsinc) and Drezz, and special thanks to smozoma and kingraph. See [Credits](#credits).

The whole of NHL '94 for the GENS as C code: about 19,000 lines, one file
per module of the original assembly and one function per routine, each named after its original
label. It plays as the cartridge does, frame for frame, without the cartridge's slowdown. Nothing
more: no rule changes, no other teams, no online play. You need your own dump of the 1 MB US/Europe cartridge
to play it; the game reads its graphics, sound and data from it.

- **Read the code:** `docs/HOW-IT-WORKS.md` (how it fits together, from power on to a frame of
  play), `docs/ROUTINES.md` (every function, its original routine and what it does),
  `docs/RAM.md` (the game's variables).
- **The game:** `game/` (play, screen, menus, sound, system). The console under it: `platform/`
  (the hardware the game touches, a window) and `runtime/`
  (the VDP, the sound chips, the pads).

## Build and play

Needs gcc (or clang), make and SDL2 (Windows: MSYS2's UCRT64 shell; `pacman -S
mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-SDL2 make`).

```
make
./build/gens94 nhl94.bin
```

The ROM is not provided: use your own dump of the cartridge. The one these runs are checked with
has the SHA-1 `7b1489ab501258133bf03e5f0892b77d04312580`.

(Windows: run it from the UCRT64 shell, or `make dist` for `build/dist/gens94.exe`, one file
with SDL2 in it. Drag a ROM onto it, or put it beside it: any `.bin` that is the game.) Save
RAM (records, a playoff) is kept in `nhl94.srm` beside the program, as the cartridge's battery
keeps it.

## Controls

| | Pad 1 | Pad 2 | Controller | In play |
|---|---|---|---|---|
| Directions | arrows | I J K L | d-pad, left stick | skate |
| A | Z | Q | west | speed burst |
| B | X | W | south | pass, switch player |
| C | C | E | east | shoot, check |
| Start | Enter | Tab | Start | pause |
| X, Y, Z, Mode | - | - | - | not used |

X, Y, Z and Mode are a six-button pad's: they can be set (in `settings.ini` or the setup screen)
but do nothing, as the cartridge reads a three-button pad.

## The settings menu

F9 opens it, Escape (or F9) closes it, and the game waits while it is open. Up / Down choose,
Enter (or Left / Right) changes; on a controller, the d-pad or stick, the south button or Start,
and Back to close. Each change is saved to `settings.ini` at once.

- **Controllers...**: the controller setup screen, each button asked for in turn, then the stick's
  dead zone.
- **Show FPS** (off): the game's new pictures a second, in the picture's top right corner (about
  60 in play).
- **Picture** (4:3): the picture's shape. 4:3 is a TV's, as the console's picture filled one: the
  rink's 256 pixels as wide as the menus' 320. Native shows its pixels square, at the largest
  whole scale that fits the window: the rink narrower than the menus, with bars beside it.

## Players

Up to four: every key, each player's controller and the controllers' buttons are in
`settings.ini` (written beside the program the first time; controllers take slots 1-8 as they are
plugged in). With keys or a controller for a third or fourth player at power on, the 4 Way Play
adaptor is plugged in, as the cartridge needs it for more than two.

## Game Speed

The cartridge's 68000 sometimes runs out of time and a frame of play takes two vblanks instead of
one: its slowdown, which the game makes up by moving everything twice as far. The C has no
instruction timing, so it has no slowdown: every frame of play takes one vblank, as on a cartridge
that never ran out of time. There is no Game Speed setting here (the SNES one has one: its C counts the
cartridge's cycles, so its slowdown is the cartridge's own).

## Check it

```
test/check.sh nhl94.bin
```

plays eight scripted runs (a full game, a 30-second one, playoffs, records, the menus; 156,000
frames) headless and checks every frame's hashes (work RAM, video
memory, Z80 RAM, the picture, the sound) against `test/expected.txt`.

## Where it comes from

The C is [ninety-four](https://github.com/1nputs/ninety-four) v0.3.6
([the release](https://github.com/1nputs/ninety-four/releases/tag/v0.3.6)) by its authors (MIT,
`LICENSE`),
which rewrote the game routine by routine and checked it frame by frame against the cartridge in
an emulator. This repository is its game alone: the additions it makes on top of the original
(game rules, roster sets, a wide rink view, netplay, save states, a menu) are taken out, each by
the original's own path, and the result checked frame for frame against it. The runtime is
[pulseman](https://github.com/1nputs/pulseman) (at `270c095`, as ninety-four v0.3.6 has it; MIT,
`runtime/LICENSE`); the YM2612 is Nuked-OPN2 (LGPL-2.1,
`runtime/third_party/nuked-opn2`); the controller setup screen, its font and the settings file
are pulseman's too. The routine and RAM names are those of the community's byte-matching rebuild
of the original assembly. The cutting down, the comments and the documents are iDNi Studios'
(MIT, `LICENSE`).

## Credits

This port is built on the community's byte-matching disassembly **NHL94Genesis** by
**abdulahmad** (https://github.com/abdulahmad/NHL94Genesis): every routine, RAM and file name here comes from it. Thanks to
**chaos**, **StaticEck**, **McMarkis (Mhopkinsinc)** and **Drezz** for their help with that
disassembly, with special thanks to **smozoma** and **kingraph**. The C is **1nput**'s [ninety-four](https://github.com/1nputs/ninety-four) v0.3.6 (MIT); the cut-down to the game alone is **iDNi Studios**' (INDIO).

Anyone building on this repository (a mod, hack, port, fork or release) must carry this credit,
near the top of their README and in the notes of every release and any text file shipped in a
release archive. See AGENTS.md.
