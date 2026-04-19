---
name: braid-devcontainer-cli
description: Use when working on the Braid C++ networking framework from macOS or any host that lacks Linux liburing support, especially when the user asks to build, configure, run, test, debug, or verify Braid through the VS Code Dev Containers CLI, devcontainer.json, Dockerfile, CMake presets, sample-server, or test-client.
---

# Braid Devcontainer CLI

## Overview

Use the project devcontainer as the default execution environment for Linux-only Braid work. The host may be macOS, but the framework depends on `io_uring` and `liburing`, so configure, build, and runtime checks should happen inside the Ubuntu devcontainer whenever possible.

## Workflow

1. Start from the repository root, normally `/Users/light8reeze/Documents/Projects/braid` on the host and `/braid` inside the container.
2. Check the worktree before making changes: `git status --short`.
3. Prefer Dev Containers CLI commands over ad hoc Docker commands when the request mentions devcontainer, containerized builds, Linux verification, `io_uring`, or `liburing`.
4. Read `references/commands.md` when exact command syntax is needed.
5. Build with the Linux CMake presets inside the container:

```bash
devcontainer exec --workspace-folder . cmake --preset linux-debug
devcontainer exec --workspace-folder . cmake --build out/build/linux-debug
```

6. If the Dev Containers CLI is unavailable, say so clearly and fall back to local inspection only. Do not claim build verification from a macOS host.

## Project Facts

- `.devcontainer/devcontainer.json` mounts the repo at `/braid` and uses `remoteUser: root`.
- `.devcontainer/Dockerfile` uses Ubuntu 24.04 and installs `build-essential`, CMake, Ninja, `liburing-dev`, Boost 1.83, Node/npm, Claude Code, and Codex.
- CMake presets are Linux-gated and write builds to `out/build/linux-debug` and `out/build/linux-release`.
- The runnable server flow is to start `sample-server`, then run `test-client` against `127.0.0.1:4832`.

## Safety

- Do not edit `.devcontainer/*` unless the user explicitly asks for devcontainer changes.
- Do not edit generated build directories such as `build/`, `out/`, `CMakeFiles/`, or `braid/build/`.
- The worktree may contain unrelated user changes; stage, commit, or modify only the requested files.
- For long-running servers, start them in a managed terminal/session and stop them before finishing unless the user asks to keep them running.

## References

- `references/commands.md`: exact Dev Containers CLI, CMake, server, client, and troubleshooting commands for Braid.
