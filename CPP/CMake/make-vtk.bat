@echo off
setlocal

set pwd=%~dp0
set pwd=%pwd:~0,-1%

@call %pwd%\setup.bat git || goto :END

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

set repo_uri=https://github.com/Kitware/VTK.git
set repo_version=v9.3.1
set repo_local=%pwd%\vtk
set output_dir=%pwd%\build-vtk
set setup_dir=%pwd%\install
set patch_file=%pwd%\workarounds\vtk-v9.3.1.diff

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

if exist %repo_local%\ goto :CLONE_DONE
mkdir %repo_local% || goto :END

git clone --branch %repo_version% --single-branch %repo_uri% %repo_local% || goto :CLONE_ERROR

echo Applying compatibility patch, please see %patch_file% for details.

git -C %repo_local% apply %patch_file% && goto :CLONE_DONE

:CLONE_ERROR
rd /s /q %repo_local%
goto :END

:CLONE_DONE

rem ----------------------------------------------------------------------------

rem Disables the warnings that occur when compiling the library using LLVM-MinGW
rem for comparison purposes with the new toolchain.
set CFLAGS=-Wno-deprecated-declarations
set CFLAGS=%CFLAGS% -Wno-deprecated-non-prototype
set CFLAGS=%CFLAGS% -Wno-format
set CFLAGS=%CFLAGS% -Wno-ignored-attributes
set CFLAGS=%CFLAGS% -Wno-implicit-const-int-float-conversion
set CFLAGS=%CFLAGS% -Wno-implicit-const-int-float-conversion
set CFLAGS=%CFLAGS% -Wno-incompatible-pointer-types
set CFLAGS=%CFLAGS% -Wno-incompatible-pointer-types-discards-qualifiers
set CFLAGS=%CFLAGS% -Wno-int-to-pointer-cast
set CFLAGS=%CFLAGS% -Wno-macro-redefined
set CFLAGS=%CFLAGS% -Wno-shift-negative-value
set CFLAGS=%CFLAGS% -Wno-unknown-attributes
set CFLAGS=%CFLAGS% -Wno-unknown-warning-option
set CXXFLAGS=%CFLAGS%

rem ----------------------------------------------------------------------------

set cmake_options=%cmake_options% -DCMAKE_SYSTEM_NAME=Windows
set cmake_options=%cmake_options% -DCMAKE_SYSTEM_PROCESSOR=x86_64
set cmake_options=%cmake_options% -DCMAKE_CROSSCOMPILING=OFF
set cmake_options=%cmake_options% -DCMAKE_INSTALL_PREFIX=%setup_dir:\=/%
set cmake_options=%cmake_options% -DCMAKE_ASM_COMPILER="%c_compiler:\=/%"
set cmake_options=%cmake_options% -DCMAKE_C_COMPILER="%c_compiler:\=/%"
set cmake_options=%cmake_options% -DCMAKE_CXX_COMPILER="%cxx_compiler:\=/%"

rem ----------------------------------------------------------------------------

if not exist %output_dir%\ mkdir %output_dir% || goto :END
if not exist %setup_dir%\ mkdir %setup_dir% || goto :END

cmake -G Ninja -S %repo_local% -B %output_dir% -Wno-dev --no-warn-unused-cli -DCMAKE_BUILD_TYPE=%build_type% %cmake_options% || goto :END
cmake --build %output_dir% --config %build_type% || goto :END
cmake --install %output_dir% --config %build_type%

:END
exit /b %errorlevel%
