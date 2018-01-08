@echo off
color 0a
mode 999,999
TITLE FLS Automode
setlocal enabledelayedexpansion
echo FLS Automode&&echo.
set STARTDATETIME=%DATE% %TIME%

for /r "%CD%\input_files" %%a IN (*) do (
echo Scanning in %%~nxa ^(%%a^) ...
file-line-splitter.exe -f "%%a" -o "%%a-done.out" -d ":"
)

for /r "%CD%\input_files" %%a IN (*.out) do (
sort "%%a" | uniq >> "%%a_unique_sorted_merged.unq"
type "%%a_unique_sorted_merged.unq">>results_merged.txt
)

sort "results_merged.txt" | uniq >> "results_unique_sorted_merged.txt"

echo.
echo Start: %STARTDATETIME%
echo Ended: %DATE% %TIME%
echo.
pause