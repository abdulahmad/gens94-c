# Handoff

Where the C-port work stands in this repository. Plan: `alignment-plan/c_ports_plan.md` in the project files.
Project-wide handoff (always current, read it first): `alignment-plan/c_ports_HANDOFF.md` in the project files; how the project is run: `alignment-plan/HARNESS.md`.

Rules: [AGENTS.md](../AGENTS.md), [RULES.md](RULES.md), [VANILLA.md](VANILLA.md).

## Done

* Phase 0: credit in the README, AGENTS.md, CLAUDE.md, docs/RULES.md, docs/VANILLA.md, this file.
* Phase 1 (part): the names gate `tools/check_names.py` and its baseline `tools/names_baseline.json`; the vanilla gate `tools/check_vanilla.sh`.

## Results (2026-11-03)

* `bash test/check.sh ROM`: 8 of 8 identical (Linux, GCC 13).
* The base (ninety-four v0.3.6) and tag v0.2.0 play the same 8 scripts identically (the base's `test/crosscheck.sh`),
  so `test/expected.txt` is reproducible from public code (next step 1 is done).
* Lockstep against the cartridge (plan E3): `test/oracle/build.sh && python3 test/oracle/lockstep.py` plays
  ninety-four's 18 lockstep vectors on this repository's `game/` (about 180k vblanks, every wait's work RAM and VDP
  state against Genesis Plus GX running the ROM): **18 of 18 pass**. Two planted bugs were caught (one in a
  vblank handler: 2 of 2 vectors failed at wait 3; one in EndOneTimer: 3 vectors failed), so the check sees this
  code. It needs a ninety-four checkout beside this one with its `tools/e2_setup.sh` and `make vectors` done.
  The HAL and run loop in that binary are ninety-four's (`platform/hal.c` is a cut of the same file without the
  counters lockstep needs); `game/` and `platform/` are unchanged.

2026-11-04: CONTRIBUTING.md added. Work stays on `claude/project-thread-4gad59`; do not merge to main. This repo stays ignored (Abdul, 2026-11-03).

## Next, in order

1. ~~Reproduce `test/expected.txt` from public code~~ (done 2026-11-03, see Results).
2. ~~Lockstep on this repository's game code~~ (done 2026-11-03, see Results).
3. Keep this repository in step with the base's renames and re-cut, if those happen (they wait for 1nput).

## Needs

* The ROM (never committed): the 1 MB US/Europe cartridge, SHA-1 `7b1489ab501258133bf03e5f0892b77d04312580`
* The asm repository beside this one: `../NHL94Genesis`.
