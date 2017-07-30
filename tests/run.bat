@echo off
del shared.dll 2>NULL
del shared.exp 2>NULL
del shared.lib 2>NULL
del shared.obj 2>NULL
del test.exe 2>NULL
del test.obj 2>NULL

cl /nologo /LD shared.cpp 1>NUL
del shared.exp
del shared.lib
del shared.obj

cl /nologo test.cpp 1>NUL
del test.obj

test.exe

del shared.dll
del test.exe
