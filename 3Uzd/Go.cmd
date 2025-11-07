@echo off

if .%USERDOMAIN% == .EULTI goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau

rem Test with input from file
courseCheck.exe courses.txt "Statistics" > result1.txt

rem Test case with default values
courseCheck.exe -t > result2.txt

