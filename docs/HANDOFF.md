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

## Next, in order

1. ~~Reproduce `test/expected.txt` from public code~~ (done 2026-11-03, see Results).
2. Keep this repository in step with the base's renames and re-cut, if those happen (they wait for 1nput).

## Needs

* The ROM (never committed): the 1 MB US/Europe cartridge, SHA-1 `7b1489ab501258133bf03e5f0892b77d04312580`
* The asm repository beside this one: `../NHL94Genesis`.
