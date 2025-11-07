
if .%USERDOMAIN% == .EULTI goto :savasPC

echo Aptiktas fakulteto kompiuteris...

path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau
test.exe > test.txt


