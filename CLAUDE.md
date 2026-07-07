# CLAUDE.md

Guidance for Claude Code (and any AI coding agent) working in this repository.

## ⛔ Read-only policy — no code changes

**Claude Code is NOT permitted to write, edit, generate, refactor, or delete code in
this repository.** This project is authored by a human, by hand. Claude Code is here for
**analysis and assistance only**.

This means Claude must **not**:

- Create, modify, or delete any source file (`.cpp`, `.hpp`, `CMakeLists.txt`, etc.).
- Apply patches, run `--fix`/auto-fix tooling, or make commits that change code.
- "Helpfully" implement a fix while explaining it — describe it instead.

If a change is warranted, **explain what to change and why, and let the human make the
edit.** When in doubt, ask before touching anything.

## ✅ What Claude Code *is* for here

- Reading and explaining the codebase, architecture, and control/ownership flow.
- Reviewing code for bugs, memory-safety issues, and design smells.
- Investigating errors and pointing to the responsible `file:line`.
- Answering questions and suggesting approaches, in prose.
- Producing **non-source** deliverables on request (e.g. review reports, notes, docs).

### Allowed file writes (non-source only)

Claude may create/update **documentation and report artifacts** when explicitly asked —
for example code review reports under `code-reviews/`. These are analysis outputs, not
project source. Everything under `src/`, the build system, and test code remains
off-limits for edits.

### Enforcement

The read-only policy is enforced, not just documented: `.claude/settings.json` denies the
`Edit`/`Write` tools on all C++ source (`**/*.cpp`, `**/*.hpp`, `src/**`, `tests/**`) and
the CMake build files. Attempts to edit those paths are blocked by the harness.

> Note: this blocks the file-editing tools. It does not sandbox arbitrary shell commands,
> so the policy still relies on Claude respecting the intent above when using `Bash`.

## Working style

- Prefer read-only tools (read, search, build/inspect) over anything that mutates source.
- Running builds or the app for **diagnosis** is fine; changing code to make them pass is not.
- Keep findings concrete: cite exact files and line numbers.

## Project context

- **Language / build:** C++20, CMake (`cmake_minimum_required 3.25`), raylib 5.5 +
  `firefly` pulled via `FetchContent`.
- **Shape:** a Snake game built on a hand-rolled engine (dependency injection, scenes,
  entity/component pipelines, event bus, state machine) under `src/`.
- **Existing analysis:** see the `code-reviews/` directory (datetime-stamped Markdown +
  PDF reports) for current findings. This directory is git-ignored.
