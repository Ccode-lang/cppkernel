nasm -f elf32 kernel.asm -o kasm.o
g++ -fno-stack-protector -m32 -c kernel.cpp -o kc.o
ld -m elf_i386 -T link.ld -o kernel.iso kasm.o kc.o
