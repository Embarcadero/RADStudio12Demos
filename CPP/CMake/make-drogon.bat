@echo off
setlocal

set pwd=%~dp0
set pwd=%pwd:~0,-1%

@call %pwd%\setup.bat git || goto :END

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

set repo_uri=https://github.com/drogonframework/drogon.git
set repo_version=v1.9.6
set repo_local=%pwd%\drogon
set output_dir=%pwd%\build-drogon
set setup_dir=%pwd%\install

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

if exist %repo_local%\ goto :CLONE_DONE
mkdir %repo_local% || goto :END

git clone --branch %repo_version% --recurse-submodules --single-branch %repo_uri% %repo_local% && goto :CLONE_DONE
rd /s /q %repo_local%
goto :END

:CLONE_DONE

rem ----------------------------------------------------------------------------

rem Build the dependencies first
if not exist %setup_dir%\share\pkgconfig\zlib.pc @call make-zlib.bat && echo. || goto :END
if not exist %setup_dir%\lib\pkgconfig\jsoncpp.pc @call make-jsoncpp.bat && echo. || goto :END

rem ----------------------------------------------------------------------------

rem Disables the warnings that occur when compiling the library using LLVM-MinGW
rem for comparison purposes with the new toolchain.
set CFLAGS=-Wno-deprecated-declarations
set CFLAGS=%CFLAGS% -Wno-format
set CFLAGS=%CFLAGS% -Wno-typedef-redefinition
set CFLAGS=%CFLAGS% -Wno-unknown-pragmas
set CXXFLAGS=%CFLAGS%

if defined c_extra_flags set CFLAGS=%c_extra_flags% %CFLAGS%
if defined cxx_extra_flags set CXXFLAGS=%cxx_extra_flags% %CXXFLAGS%

rem ----------------------------------------------------------------------------

set cmake_options=%cmake_options% -DCMAKE_SYSTEM_NAME=Windows
set cmake_options=%cmake_options% -DCMAKE_SYSTEM_PROCESSOR=x86_64
set cmake_options=%cmake_options% -DCMAKE_CROSSCOMPILING=OFF
set cmake_options=%cmake_options% -DCMAKE_INSTALL_PREFIX=%setup_dir:\=/%
set cmake_options=%cmake_options% -DCMAKE_ASM_COMPILER="%c_compiler:\=/%"
set cmake_options=%cmake_options% -DCMAKE_C_COMPILER="%c_compiler:\=/%"
set cmake_options=%cmake_options% -DCMAKE_CXX_COMPILER="%cxx_compiler:\=/%"

rem Extra CMake options to build the third-party library.
set cmake_options=%cmake_options% -DBUILD_EXAMPLES=OFF
set cmake_options=%cmake_options% -DBUILD_DOC=OFF

rem ----------------------------------------------------------------------------

if not exist %output_dir%\ mkdir %output_dir% || goto :END
if not exist %setup_dir%\ mkdir %setup_dir% || goto :END

cmake -G Ninja -S %repo_local% -B %output_dir% -Wno-dev --no-warn-unused-cli -DCMAKE_BUILD_TYPE=%build_type% %cmake_options% || goto :END
cmake --build %output_dir% --config %build_type% || goto :END
cmake --install %output_dir% --config %build_type%

:END
exit /b %errorlevel%
