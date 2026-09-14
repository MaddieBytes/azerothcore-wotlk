#Requires -Version 7.0
<#
.SYNOPSIS
Runs CMake with a case-insensitively unique Windows child environment.
.EXAMPLE
./apps/compiler/windows-cmake.ps1 --build ../build/azerothcore-port --config RelWithDebInfo --target worldserver
#>
# Use raw arguments so CMake options such as -P and -D are not bound as
# PowerShell common parameters. Quote '--' when forwarding native build options.
$ErrorActionPreference = 'Stop'
if (-not $IsWindows) {
    throw 'This wrapper requires Windows and PowerShell 7 or newer.'
}

$start = [System.Diagnostics.ProcessStartInfo]::new()
$start.FileName = (Get-Command cmake.exe -CommandType Application -ErrorAction Stop).Source
$start.UseShellExecute = $false
$start.WorkingDirectory = (Get-Location).ProviderPath
foreach ($argument in $args) {
    $start.ArgumentList.Add($argument)
}

# Rebuild the actual child environment; changing $env:Path can leave a second
# differently cased entry in a malformed inherited Windows environment block.
$inherited = [Environment]::GetEnvironmentVariables('Process')
$start.Environment.Clear()
$keys = [string[]] @($inherited.Keys)
[Array]::Sort($keys, [StringComparer]::Ordinal)
foreach ($key in $keys) {
    if (-not $start.Environment.ContainsKey($key)) {
        $start.Environment[$key] = $inherited[$key]
    }
}
# Ordinal ordering prefers PATH over Path: Codex's PATH includes its runtime
# additions. Other case collisions follow the same deterministic first-wins rule.
# Do not reuse an MSBuild worker that inherited a previous, malformed environment.
$start.Environment['MSBUILDDISABLENODEREUSE'] = '1'

$child = [System.Diagnostics.Process]::Start($start)
try {
    $child.WaitForExit()
    $exitCode = $child.ExitCode
} finally {
    $child.Dispose()
}
exit $exitCode
