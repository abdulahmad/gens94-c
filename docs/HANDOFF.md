# Handoff

Where the C-port work stands in this repository. Plan: `alignment-plan/c_ports_plan.md` in the project files.
Rules: [AGENTS.md](../AGENTS.md), [RULES.md](RULES.md), [VANILLA.md](VANILLA.md).

## Done

* Phase 0: credit in the README, AGENTS.md, CLAUDE.md, docs/RULES.md, docs/VANILLA.md, this file.
* Phase 1 (part): the names gate `tools/check_names.py` and its baseline `tools/names_baseline.json`; the vanilla gate `tools/check_vanilla.sh`.

## Next, in order

1. **Reproduce `test/expected.txt` from public code** (needs the ROM): its hashes came from ninety-four commit
   d503a46, which is not public. Play the 8 scripts on the base (NHL94Genesis-C-Port, v0.3.6) and compare. Ask INDIO
   for d503a46 if they differ.
2. Keep this repository in step with the base's renames and re-cut, if those happen (they wait for 1nput).

## Needs

* The ROM (never committed): the 1 MB US/Europe cartridge, SHA-1 `7b1489ab501258133bf03e5f0892b77d04312580`
* The asm repository beside this one: `../NHL94Genesis`.
