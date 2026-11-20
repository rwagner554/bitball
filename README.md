# bitball

An SDL3 game project (C++20).

## Requirements

- **CMake 3.21+**
- **Visual Studio 2019 or newer** with the *Desktop development with C++*
  workload (Community/Professional/Enterprise/Build Tools all work).

You don't need Visual Studio on a particular drive or in a particular folder —
CMake looks it up in the registry, and `scripts/build.ps1` asks `vswhere` where
it is.

## Build

### Command line (easiest)

```powershell
.\scripts\build.ps1                        # Debug
.\scripts\build.ps1 -Configuration Release
```

The script finds your Visual Studio install, picks the matching CMake
generator, configures on first run, then builds.

### VSCode

1. Install the **CMake Tools** extension.
2. It will offer the presets in `CMakePresets.json`:
   - `vs2022` for Visual Studio 2022
   - `vs2026` for Visual Studio 2026
3. Pick one, then build/run with the status-bar buttons or F5.

### Plain CMake

```powershell
cmake --preset vs2022
cmake --build --preset vs2022-debug
```

Output lands in `build/vs17/Debug/bitball.exe` (or `build/vs18/...`). `SDL3.dll`
is copied next to the executable automatically after every build, so the game
runs straight from Explorer or the debugger.

Adding a source file means adding it to the `add_executable(bitball ...)` list
in `CMakeLists.txt`.

## SDL3

The prebuilt **SDL3 development package** (`SDL3-devel-*-VC`) lives in
`third_party/SDL3` and is committed, so both machines get the exact same
version. To upgrade, replace that folder with the contents of a newer
`SDL3-devel-*-VC.zip`.

`CMakeLists.txt` sets `SDL_CPU_X64`/`SDL_CPU_X86`/`SDL_CPU_ARM64` before calling
`find_package(SDL3)` because the shipped `SDL3Config.cmake` expects the consumer
to declare the target architecture, and it selects `lib/<arch>/SDL3.lib`
accordingly.
