# Agent Instructions

## Core rules

- Read `docs/INDEX.md` before loading project documentation.
- Load only the documents relevant to the current task.
- Do not recursively read all files under `docs/`.
- Do not read `docs/archive/` unless historical context is explicitly required.
- Prefer current source code over stale documentation when they conflict.
- When behavior, architecture, commands, or conventions change, update the smallest relevant document.

## Source priority

When sources conflict, use this priority unless a task says otherwise:

1. Explicit user/task instructions
2. `docs/current/`
3. Relevant project documentation referenced by `docs/INDEX.md`
4. Source code and tests
5. `docs/decisions/`
6. `docs/archive/`

## Working procedure

1. Read `docs/INDEX.md`.
2. Identify the minimum set of relevant documents.
3. Read those documents only.
4. Inspect the relevant source files.
5. Make the change.
6. Run the relevant checks from `docs/commands.md`.
7. Update documentation only if the documented behavior changed.

## Commit messages

- Subject: `<type>: <summary>`, e.g. `refactor: doubling を Doubling に改名し命名を規約に揃える`.
- `<type>` is one of `feat`, `fix`, `perf`, `refactor`, `docs`, `test`, `ci`, `chore`.
- Write `<summary>` in Japanese as a plain-form sentence of what the commit does (`〜する`, `〜を追加する`), with no trailing period.
- Do not write the PR number `(#123)`; squash merge appends it.
- Body (optional): in Japanese, explain why and what changed; use `-` bullets for multiple points.

## Branch names

- Format: `<type>/<kebab-case-summary>` in lowercase English, e.g. `feat/static-segment-tree-2d`, `fix/reference-pipe-escape`.
- `<type>` uses the same set as commit messages (not `feature/` or other prefixes).
- See `docs/current/git-workflow.md` for where to branch from and when to commit or open PRs.
