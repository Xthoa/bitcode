@echo off
src2asm %1 %1.asm
nasm %1.asm -f bin -o %2
