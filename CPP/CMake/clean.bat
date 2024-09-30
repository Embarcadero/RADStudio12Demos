@echo off
setlocal

set pwd=%~dp0
set pwd=%pwd:~0,-1%

if exist %pwd%\install\             rd /s /q %pwd%\install
if exist %pwd%\build-googletest\    rd /s /q %pwd%\build-googletest
if exist %pwd%\build-zlib\          rd /s /q %pwd%\build-zlib
if exist %pwd%\build-brotli\        rd /s /q %pwd%\build-brotli
if exist %pwd%\build-vtk\           rd /s /q %pwd%\build-vtk
if exist %pwd%\build-opencv\        rd /s /q %pwd%\build-opencv
if exist %pwd%\build-ninja\         rd /s /q %pwd%\build-ninja
if exist %pwd%\build-jsoncpp\       rd /s /q %pwd%\build-jsoncpp
if exist %pwd%\build-drogon\        rd /s /q %pwd%\build-drogon
if exist %pwd%\build-libsimdpp\     rd /s /q %pwd%\build-libsimdpp
if exist %pwd%\build-vcl\           rd /s /q %pwd%\build-vcl
if exist %pwd%\build-fmx\           rd /s /q %pwd%\build-fmx
if exist %pwd%\build-package\       rd /s /q %pwd%\build-package
if exist %pwd%\build-console\       rd /s /q %pwd%\build-console

exit /b %errorlevel%
