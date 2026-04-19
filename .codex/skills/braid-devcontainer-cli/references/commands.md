# Braid Devcontainer Commands

Run from the host repo root unless noted:

```bash
cd /Users/light8reeze/Documents/Projects/braid
```

## Check Tooling

```bash
devcontainer --version
docker --version
```

If `devcontainer` is missing, install/use the VS Code Dev Containers CLI before claiming container verification.

## Build Or Rebuild The Container

```bash
devcontainer build --workspace-folder .
```

Use this when `.devcontainer/Dockerfile`, `.devcontainer/devcontainer.json`, or base dependencies change.

## Run Commands Inside The Container

```bash
devcontainer exec --workspace-folder . pwd
devcontainer exec --workspace-folder . bash -lc 'cmake --version && g++ --version && pkg-config --libs liburing'
```

The workspace path inside the container is `/braid`.

## Configure And Build

Debug:

```bash
devcontainer exec --workspace-folder . cmake --preset linux-debug
devcontainer exec --workspace-folder . cmake --build out/build/linux-debug
```

Release:

```bash
devcontainer exec --workspace-folder . cmake --preset linux-release
devcontainer exec --workspace-folder . cmake --build out/build/linux-release
```

Portable fallback inside the container:

```bash
devcontainer exec --workspace-folder . cmake -S . -B build
devcontainer exec --workspace-folder . cmake --build build
```

## Run Server And Client

Start sample server in one terminal/session:

```bash
devcontainer exec --workspace-folder . ./out/build/linux-debug/sample-server/sample-server
```

Run test client in another terminal/session:

```bash
devcontainer exec --workspace-folder . ./out/build/linux-debug/test-client/test-client 10000
```

Use a smaller client count for smoke tests:

```bash
devcontainer exec --workspace-folder . ./out/build/linux-debug/test-client/test-client 10
```

## Inspect Generated Artifacts

```bash
devcontainer exec --workspace-folder . ls -la out/build/linux-debug
devcontainer exec --workspace-folder . find out/build/linux-debug -maxdepth 3 -type f -perm -111
```

## Clean Build Output

Only remove generated build directories when explicitly requested:

```bash
devcontainer exec --workspace-folder . rm -rf out/build/linux-debug
devcontainer exec --workspace-folder . rm -rf build
```

## Common Failure Notes

- `cmake --preset linux-debug` failing on macOS is expected because the preset is Linux-gated.
- Missing `liburing.h` means the command likely ran on the host or the container image is stale.
- If `devcontainer exec` cannot find a running container, run `devcontainer build --workspace-folder .` first, then retry.
