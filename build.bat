@echo OFF

setlocal ENABLEEXTENSIONS

FOR /F "usebackq tokens=3*" %%A IN (`REG QUERY "HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Microsoft\VisualStudio\14.0" /v InstallDir`) DO (
    set appdir=%%A %%B
    )

call "%appdir%\..\..\vc\bin\amd64_x86\vcvarsamd64_x86.bat"

msbuild .\vs\abscission_sdl_engine.sln /m /p:Configuration=Release /p:Platform=x64 > .\build\x64\build.log

msbuild .\vs\abscission_sdl_engine.sln /m /p:Configuration=Release /p:Platform=x86 > .\build\x86\build.log
pause