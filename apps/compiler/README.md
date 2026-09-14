## How to compile:

### Windows (CMake / Visual Studio)

From PowerShell 7 or newer, use `windows-cmake.ps1` in place of `cmake` when configuring or building.
It forwards arguments unchanged, uses `cmake.exe` from PATH, keeps the current directory, and returns CMake's exit code.
For example, from the repository root with an existing build directory:

```powershell
./apps/compiler/windows-cmake.ps1 --build ../build/azerothcore-port --config RelWithDebInfo --target worldserver --parallel 4
./apps/compiler/windows-cmake.ps1 --build ../build/azerothcore-port --config RelWithDebInfo --target modules --parallel 4
```

Adjust the build directory, configuration and target to your existing CMake configuration.
Building `worldserver` also builds and links its configured modules. This does not install binaries or start services.
For a persistent MSBuild log, append `'--' /fl /flp:logfile=build.log`.
Quote the literal `'--'` separator: PowerShell consumes an unquoted `--` when calling a script.

The Codex Windows command environment can contain both `Path` and `PATH` (the latter adds its PowerShell runtime).
MSBuild's .NET Framework `CL` task then fails while creating `ProcessStartInfo.EnvironmentVariables` with
`MSB6001: Item has already been added. Key in dictionary: 'Path' Key being added: 'PATH'`.
An up-to-date build can hide this because no compiler is launched.
The wrapper constructs a fresh child environment with case-insensitively unique names, preferring uppercase `PATH`
when both variants exist. Other case collisions use ordinal-first spelling and value.
It also disables MSBuild node reuse for the child so a worker with an old environment cannot reintroduce the failure.
Only the child environment changes; no machine/user environment edits, elevation, or process cleanup are required.

### Unix

first of all, if you need some custom configuration you have to copy
/conf/dist/config.sh in /conf/config.sh and configure it

* for a "clean" compilation you must run all scripts in their order:

        ./1-clean.sh
        ./2-configure.sh
        ./3-build.sh

* if you add/rename/delete some sources and you need to compile it you have to run:

        ./2-configure.sh
        ./3-build.sh

* if you have modified code only, you just need to run

        ./3-build.sh


## compiler.sh 

compiler.sh script contains an interactive menu to clean/compile/build. You can also run actions directly by command lines specifying the option.
Ex:
  ./compiler.sh 3  

It will start the build process (it's equivalent to ./3-build.sh)

## Note:

For an optimal development process and **really faster** compilation time, is suggested to use clang instead of gcc
