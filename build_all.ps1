# Build All Projects
$ErrorActionPreference = "Continue"
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$logFile = Join-Path $scriptDir "build_all.log"

Write-Host "Building all projects..."

# Delete old log if it exists
if (Test-Path $logFile) {
    Remove-Item $logFile -Force
}

# Run MSBuild and tee output to log file
$msbuildPath = "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
$solutionPath = Join-Path $scriptDir "Helbreath.sln"

& $msbuildPath $solutionPath /p:Configuration=Debug /p:Platform=x86 2>&1 | Tee-Object -FilePath $logFile
