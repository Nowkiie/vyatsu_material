cd "D:\work\projects\forsunka_prj\"
D:
del e1sign.map
del e1sign.lst
"C:\Program Files\Atmel\AVR Tools\AvrAssembler\avrasm32.exe" -fI "D:\work\projects\forsunka_prj\E1sign.asm" -o "e1sign.hex" -d "e1sign.obj" -I "D:\work\projects\forsunka_prj" -I "C:\Program Files\Atmel\AVR Tools\AvrAssembler\AppNotes"
