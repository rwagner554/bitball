# Finds the Visual Studio install that owns the C++ toolset (any edition, any
# drive) and builds bitball with it. Run it from anywhere:
#
#   .\scripts\build.ps1                 # Debug
#   .\scripts\build.ps1 -Configuration Release
#
# It configures automatically the first time, then just builds.

param(
    [ValidateSet("Debug", "Release")]
    [string] $Configuration = "Debug"
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot

# vswhere ships with every Visual Studio 2017+ installer at this fixed path,
# regardless of where Visual Studio itself was installed.
$vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $vswhere)) {
    throw "vswhere.exe not found. Install Visual Studio (or Build Tools) with the 'Desktop development with C++' workload."
}

$vcTools = "Microsoft.VisualStudio.Component.VC.Tools.x86.x64"

$installPath = & $vswhere -latest -products * -requires $vcTools -property installationPath
if (-not $installPath) {
    throw "No Visual Studio installation with the MSVC toolset found. Install the 'Desktop development with C++' workload."
}

$version = & $vswhere -latest -products * -requires $vcTools -property installationVersion
$major = [int] ($version.Split(".")[0])

$generator = switch ($major) {
    18 { "Visual Studio 18 2026" }
    17 { "Visual Studio 17 2022" }
    16 { "Visual Studio 16 2019" }
    default { throw "Visual Studio $version is not supported by this script (need 2019 or newer)." }
}

Write-Host "Visual Studio $version at $installPath"
Write-Host "Generator: $generator"

# Same tree the matching CMakePresets.json preset uses, so the CLI and
# VSCode's CMake Tools extension share one build directory.
$buildDir = Join-Path $repoRoot "build\vs$major"

cmake -S $repoRoot -B $buildDir -G $generator -A x64
if ($LASTEXITCODE -ne 0) { throw "CMake configure failed." }

cmake --build $buildDir --config $Configuration
if ($LASTEXITCODE -ne 0) { throw "Build failed." }

Write-Host "`nBuilt: $buildDir\$Configuration\bitball.exe"
