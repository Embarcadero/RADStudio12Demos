rem ----------------------------------------------------------------------------

set build_type=Release

rem ----------------------------------------------------------------------------

if not defined BDS goto :INVALID_BDS_VAR
if not exist "%BDS%\" goto :INVALID_BDS_VAR

goto :START

:INVALID_BDS_VAR
echo The BDS variable is not valid.
echo Before continuing, run "<BDS DIR>\bin\rsvars.bat".
exit /b 1

:START

rem ----------------------------------------------------------------------------

set apps=cmake ninja %~1

for %%a in (%apps%) do (
    where %%a > nul 2> nul
    if ERRORLEVEL 1 (
        echo %%a is not available on the PATH environment variable.
        set app_not_found=true
    )
)

if "%app_not_found%"=="true" (
    echo Before continuing, ensure that all required applications are available on the PATH environment variable.
    exit /b 1
)

rem ----------------------------------------------------------------------------

set cc=
set cflags=
set cxx=
set cxxflags=
set rc=
set rcflags=

set pythonpath=
set pythonhome=

rem ----------------------------------------------------------------------------

set c_compiler=%BDS%\bin64\bcc64x.exe
set cxx_compiler=%BDS%\bin64\bcc64x.exe

rem ----------------------------------------------------------------------------
