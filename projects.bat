cd /d "%~dp0"
mklink /d /j "E:\book-code" "H:\rover\rover-self-work\cpp\book-code" 
set PATH=%~dp0;E:\book-code;%PATH%
::premake5 --file=projects.lua vs2013
premake5 --file=projects.lua vs2005
pause