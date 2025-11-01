$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$buildDir = Join-Path $root "build"

if (-Not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

Set-Location $buildDir

cmake .. -G "Visual Studio 17 2022" -A x64

Write-Host "Build finished."