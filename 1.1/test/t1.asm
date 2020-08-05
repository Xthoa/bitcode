;t1.asm
db 0x0a		;nop
db 0x0c		;pause
db 0x70,3
db 0x63,0	;d.0 = 10
	dd 10
db 0x13		;system('echo')
	db 4,"echo",0
db 0x64,0	;d.0 += 2
	dd 2
db 0x0c		;pause
;db 0x0f		;cls
db 0x11,0	;script python ...
	db 7,"test.py"
	dd 21
	db "print('Hello world!')"
db 0x0c		;pause
db 0x66,0	;d.0 /= 0
	dd 0
db 0x0c		;pause
db 0x09		;exit