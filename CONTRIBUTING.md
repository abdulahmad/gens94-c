# Contributing to gens94-c

INDIO's Genesis C-port cross-check (a cut of ninety-four v0.3.6). Abdul: ignore this repo from 2026-11-03 — no work
or cross-checks on it; the Genesis base is NHL94Genesis-C-Port.

Read [AGENTS.md](AGENTS.md) first (gates, units, credit). Alignment rules: [docs/RULES.md](docs/RULES.md). Where this
repo stands: [docs/HANDOFF.md](docs/HANDOFF.md). What "vanilla" allows: [docs/VANILLA.md](docs/VANILLA.md).

Work stays on `claude/project-thread-4gad59`. Do not branch from `main` and do not merge to `main`. PRs from that
branch are for review only.

This repository is a derivative of [NHL94Genesis](https://github.com/abdulahmad/NHL94Genesis). Keep the credit near
the top of the README and in every release, as AGENTS.md requires.

## Gates

| Gate | Command |
|---|---|
| Build | `make` |
| Frames | `bash test/check.sh ROM` |
| Names | `python3 tools/check_names.py --check` |
| Vanilla | `tools/check_vanilla.sh` |

A change passes only when those programs say so. Other games' names never go in comments; lineage lives in the asm
repo's `docs/name_map.csv`.

The ROM is never committed.
