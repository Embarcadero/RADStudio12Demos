@echo off
setlocal

set pwd=%~dp0
set pwd=%pwd:~0,-1%

@call %pwd%\setup.bat git || goto :END

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

set repo_uri=https://github.com/opencv/opencv.git
set repo_version=4.10.0
set repo_local=%pwd%\opencv
set output_dir=%pwd%\build-opencv
set setup_dir=%pwd%\install

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

if exist %repo_local%\ goto :CLONE_DONE
mkdir %repo_local% || goto :END

git clone --branch %repo_version% --single-branch %repo_uri% %repo_local% && goto :CLONE_DONE
rd /s /q %repo_local%
goto :END

:CLONE_DONE

rem ----------------------------------------------------------------------------

rem Build the dependencies first
if not exist "%setup_dir%\lib\cmake\vtk-*.<" @call make-vtk.bat && echo. || goto :END

rem ----------------------------------------------------------------------------

rem Disables the warnings that occur when compiling the library using LLVM-MinGW
rem for comparison purposes with the new toolchain.
rem
rem NOTE: Some warnings are not suppressed because they are replaced by
rem       additional flags that are passed on afterwards (e.g. -Wall, -W).
set CFLAGS=-Wno-macro-redefined
set CFLAGS=%CFLAGS% -Wno-switch
set CFLAGS=%CFLAGS% -Wno-unknown-pragmas
set CFLAGS=%CFLAGS% -Wno-unused-but-set-variable
set CFLAGS=%CFLAGS% -Wno-unused-const-variable
set CFLAGS=%CFLAGS% -Wno-unused-parameter
set CFLAGS=%CFLAGS% -Wno-unused-private-field
set CFLAGS=%CFLAGS% -Wno-unused-variable
set CXXFLAGS=%CFLAGS%

rem ----------------------------------------------------------------------------

set cmake_options=%cmake_options% -DCMAKE_SYSTEM_NAME=Windows
set cmake_options=%cmake_options% -DCMAKE_SYSTEM_PROCESSOR=x86_64
set cmake_options=%cmake_options% -DCMAKE_CROSSCOMPILING=OFF
set cmake_options=%cmake_options% -DCMAKE_INSTALL_PREFIX=%setup_dir:\=/%
set cmake_options=%cmake_options% -DCMAKE_ASM_COMPILER="%c_compiler:\=/%"
set cmake_options=%cmake_options% -DCMAKE_C_COMPILER="%c_compiler:\=/%"
set cmake_options=%cmake_options% -DCMAKE_CXX_COMPILER="%cxx_compiler:\=/%"

rem Extra CMake options to build the third-party library.
set cmake_options=%cmake_options% -DPython3_EXECUTABLE=%pythonhome%\python.exe

rem ----------------------------------------------------------------------------

if not exist %output_dir%\ mkdir %output_dir% || goto :END
if not exist %setup_dir%\ mkdir %setup_dir% || goto :END

cmake -G Ninja -S %repo_local% -B %output_dir% -Wno-dev --no-warn-unused-cli -DCMAKE_BUILD_TYPE=%build_type% %cmake_options% || goto :END
cmake --build %output_dir% --config %build_type% || goto :END
cmake --install %output_dir% --config %build_type%

:END
exit /b %errorlevel%
