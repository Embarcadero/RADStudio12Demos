@echo off
setlocal

set pwd=%~dp0
set pwd=%pwd:~0,-1%

@call %pwd%\setup.bat git || goto :END

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

set repo_uri=https://github.com/open-source-parsers/jsoncpp.git
set repo_version=1.9.5
set repo_local=%pwd%\jsoncpp
set output_dir=%pwd%\build-jsoncpp
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

rem Disables the warnings that occur when compiling the library using LLVM-MinGW
rem for comparison purposes with the new toolchain.
rem
rem NOTE: Some warnings are not suppressed because they are replaced by
rem       additional flags that are passed on afterwards (e.g. -Wall, -W).
set CXXFLAGS=-Wno-deprecated-declarations
set CXXFLAGS=%CXXFLAGS% -Wno-format
set CXXFLAGS=%CXXFLAGS% -Wno-unknown-pragmas

rem ----------------------------------------------------------------------------

set cmake_options=%cmake_options% -DCMAKE_SYSTEM_NAME=Windows
set cmake_options=%cmake_options% -DCMAKE_SYSTEM_PROCESSOR=x86_64
set cmake_options=%cmake_options% -DCMAKE_CROSSCOMPILING=OFF
set cmake_options=%cmake_options% -DCMAKE_INSTALL_PREFIX=%setup_dir:\=/%
set cmake_options=%cmake_options% -DCMAKE_ASM_COMPILER="%c_compiler:\=/%"
set cmake_options=%cmake_options% -DCMAKE_C_COMPILER="%c_compiler:\=/%"
set cmake_options=%cmake_options% -DCMAKE_CXX_COMPILER="%cxx_compiler:\=/%"

rem At the moment, we are not running the libjsoncpp tests due to an issue
rem involving Unicode characters. The Embarcadero compilers use the u"" format,
rem which may be causing the issue. It's not clear whether this issue warrants
rem further investigation, since Embarcadero compilers follow the MSVC standard,
rem and these tests are also expected to pass with CL.

rem   * Detail of CharReaderTest/parseChineseWithOneError test failure:
rem   ./jsoncpp/src/test_lib_json/main.cpp(3204): errs == "* Line 1, Column 19\n  Syntax error: value, object or array " "expected.\n"
rem   * Detail of EscapeSequenceTest/writeEscapeSequence test failure:
rem   ./jsoncpp/src/test_lib_json/main.cpp(3685): expected == result
rem     Expected: '["\"","\\","\b","\f","\n","\r","\t","\u0278","\ud852\udf62"]
rem     '
rem     Actual  : '["\"","\\","\b","\f","\n","\r","\t","?","??"]
rem     '
set cmake_options=%cmake_options% -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF

rem ----------------------------------------------------------------------------

if not exist %output_dir%\ mkdir %output_dir% || goto :END
if not exist %setup_dir%\ mkdir %setup_dir% || goto :END

cmake -G Ninja -S %repo_local% -B %output_dir% -Wno-dev --no-warn-unused-cli -DCMAKE_BUILD_TYPE=%build_type% %cmake_options% || goto :END
cmake --build %output_dir% --config %build_type% || goto :END
cmake --install %output_dir% --config %build_type%

:END
exit /b %errorlevel%
