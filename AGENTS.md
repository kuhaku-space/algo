# Agent Instructions

## Documentation

### Reading

- Read only documentation relevant to the current task.
- Access known files directly; use `docs/INDEX.md` only when locating documentation.
- Prefer targeted searches and relevant sections over entire files.
- Reuse information already available in the current context.
- Check related documentation when changes may affect other components.
- Prioritize current specifications and source code over outdated documentation.

### Writing

- Keep documentation concise, accurate, and nonredundant.
- Organize documents by topic with descriptive headings.
- Maintain a single source of truth; link instead of duplicating content.
- Separate current specifications from historical decisions.
- Update the relevant documentation when behavior, architecture, commands, or conventions change.
- Update `docs/INDEX.md` when the documentation structure changes.

## Checks

- Run the relevant checks from `docs/commands.md` after making changes.

## Commit messages

- Follow Conventional Commits without scope, using types `feat`, `fix`, `perf`, `refactor`, `docs`, `test`, `ci`, `chore`.
- Write the description and body in Japanese plain form (`〜する`), with no trailing period or PR number.

## Branch names

- Format: `<type>/<kebab-case-summary>` in lowercase English, e.g. `feat/static-segment-tree-2d`, `fix/reference-pipe-escape`.
- `<type>` uses the same set as commit messages (not `feature/` or other prefixes).
- See `docs/current/git-workflow.md` for where to branch from and when to commit or open PRs.

## Pull requests

- Enable auto-merge whenever you open a PR: `gh pr create --fill && gh pr merge --auto --squash`.
- See `docs/current/git-workflow.md` for details.
