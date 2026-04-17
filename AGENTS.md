# Agent Instructions

## Project Overview

Braid is a C++20 networking framework built around an `io_uring` service loop, worker threads, serialized task execution, intrusive reference counting, and object pooling. The primary library code lives under `braid/src`, with runnable targets in `braid/`, `sample-server/`, and `test-client/`.

Keep changes small and consistent with the current design. This repository is performance- and concurrency-sensitive; avoid broad refactors unless the user explicitly asks for them.

## Repository Layout

- `CMakeLists.txt` configures the top-level project and adds `braid`, `sample-server`, and `test-client`.
- `CMakePresets.json` defines Linux Ninja presets that write to `out/build/<preset>`.
- `braid/BraidServer.cc` is the main executable entry for the core server target.
- `braid/src/util` contains common macros, utility headers, and logging.
- `braid/src/task` contains `RefCountable`, `ObjectPtr`, `Task`, `TaskSerializer`, and `TaskDistributor`.
- `braid/src/memory` contains header-only object pool infrastructure.
- `braid/src/service` contains service/session/actor logic, worker threads, `io_uring` request queues, and IO operation classes.
- `sample-server` registers message handlers and exercises service behavior.
- `test-client` is a Linux socket/epoll load client.
- `.devcontainer` defines an Ubuntu-based development environment with Boost, liburing, CMake, and compiler tooling.

Generated build artifacts may exist in `build/`, `out/`, `CMakeFiles/`, and `braid/build/`. Do not edit those artifacts as source.

## Build And Run

Required dependencies:

- CMake 3.20+
- C++20 compiler
- Linux with `liburing` development headers and library
- Boost 1.83 or newer
- Ninja when using the presets

Preferred configure/build commands on Linux:

```bash
cmake --preset linux-debug
cmake --build out/build/linux-debug
```

Portable fallback:

```bash
cmake -S . -B build
cmake --build build
```

Runnable targets are expected under the chosen build directory. Typical manual flow is to start the server target, then run `test-client` against `127.0.0.1:4832`.

There is no dedicated automated test suite in the current tree. For verification, build the changed target at minimum. For networking behavior changes, use `sample-server` and `test-client` manually when the environment supports `io_uring`.

## Coding Conventions

- Use C++20.
- Put framework code in namespace `braid`.
- Follow the existing file organization: public headers under `include/braid/...`, implementations under matching `src/...` folders.
- Preserve existing naming style: classes use `PascalCase`; functions, locals, and members mostly use `snake_case`; private data members commonly end with `_`.
- Prefer existing primitives over new abstractions:
  - `ObjectPtr<T>` for intrusive pointers to `RefCountable` types.
  - `TaskSerializer::request_task` for serialized work.
  - `g_task_distributor` for worker-side task distribution.
  - `g_io_pool` and `PooledObject::on_zero_ref` for pooled IO operations.
- Use `NON_COPYABLE` for non-copyable classes when matching existing code.
- Keep includes local and explicit. Use existing public include roots such as `<braid/service/Service.h>`.
- Comments can be in Korean or English if they match nearby code, but avoid adding obvious comments.

## Concurrency And Lifetime Notes

- `RefCountable` uses intrusive reference counting. When storing or passing pooled/ref-counted objects, make ownership explicit and avoid raw-pointer lifetime assumptions.
- `Task` increments references for `RefCountable` arguments and releases them on destruction. Be careful when adding new task argument types.
- `TaskSerializer` queues work and can enter `DESTROYING`/`DESTROYED`; do not enqueue work after destruction begins.
- `ServiceSession` reuses a fixed session pool and returns sessions through `Service::on_session_closed`.
- IO operations are acquired through `Service::request_io<T>` and released through their `on_zero_ref` implementation.
- `IORequestQueue` owns an `io_uring` instance per worker thread and flushes queued operations before submit.
- Avoid blocking work inside worker-thread routines or serialized task handlers unless the user requests it.

## CMake Notes

- Add new service source files to `braid/src/service/CMakeLists.txt`.
- Add new task source files to `braid/src/task/CMakeLists.txt`.
- Add new public headers under the relevant `include/braid/...` directory.
- Keep dependency linkage close to the target that needs it.
- Do not introduce package managers or vendored dependencies without user approval.

## Change Hygiene

- Check `git status --short` before editing. The worktree may already contain user changes; do not revert or overwrite unrelated modifications.
- Do not edit `.devcontainer/*`, `.vscode/*`, or generated build outputs unless the user request is specifically about those files.
- Keep patches focused on the requested behavior.
- If build verification is not possible because the host is not Linux or lacks `liburing`/Boost, state that clearly in the final response.
