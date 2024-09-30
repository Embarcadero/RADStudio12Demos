@echo off
setlocal

set pwd=%~dp0
set pwd=%pwd:~0,-1%

echo Building GTest...
@call %pwd%\make-googletest.bat || goto :END
echo.

echo Building Z-lib...
@call %pwd%\make-zlib.bat || goto :END
echo.

echo Building Brotli...
@call %pwd%\make-brotli.bat || goto :END
echo.

echo Building VTK...
@call %pwd%\make-vtk.bat || goto :END
echo.

echo Building OpenCV...
@call %pwd%\make-opencv.bat || goto :END
echo.

echo Building Ninja...
@call %pwd%\make-ninja.bat || goto :END
echo.

echo Building jsoncpp...
@call %pwd%\make-jsoncpp.bat || goto :END
echo.

echo Building Drogon...
@call %pwd%\make-drogon.bat || goto :END
echo.

echo Building libsimdpp...
@call %pwd%\make-libsimdpp.bat || goto :END
echo.

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

echo -- All third-party libraries have been successfully built.
echo.
echo.

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

rem The following tests refer to RAD Studio projects. Therefore, if you are
rem using the original LLVM-MinGW compiler, they will fail during the build.

echo Building VCL Demo...
@call %pwd%\make-vcl.bat || goto :END
echo.

echo Building FMX Demo (Runtime Packages)...
@call %pwd%\make-fmx.bat || goto :END
echo.

echo Building Package...
@call %pwd%\make-package.bat || goto :END
echo.

echo Building Console...
@call %pwd%\make-console.bat || goto :END
echo.

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

echo -- All RAD Studio projects have been successfully built.
echo.
echo.

rem ----------------------------------------------------------------------------

:END
exit /b %errorlevel%
