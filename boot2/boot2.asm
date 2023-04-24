;
;    File: boot_v2.asm
;    Author: Tanmay Verma
;    Date  : 12/01/2015
;    Writing a simple bootloader that prints 'Hello World on the screen'. 
;

section .boot
bits 16
global boot
boot:
	mov ax, 0x2401
	int 0x15

	mov ax, 0x3
	int 0x10

	mov [disk],dl

	mov ah, 0x2    ;read sectors
	mov al, 6      ;sectors to read
	mov ch, 0      ;cylinder idx
	mov dh, 0      ;head idx
	mov cl, 2      ;sector idx
	mov dl, [disk] ;disk idx
	mov bx, copy_target;target pointer
	int 0x13
	cli
	lgdt [gdt_pointer]
	mov eax, cr0
	or eax,0x1
	mov cr0, eax
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp CODE_SEG:boot2
gdt_start:
	dq 0x0
gdt_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
gdt_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
gdt_end:
gdt_pointer:
	dw gdt_end - gdt_start
	dd gdt_start
disk:
	db 0x0
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 510 - ($-$$) db 0
dw 0xaa55
; 512 Bytes filled
copy_target:
bits 32
	hello: db "Hello from beyond 512 Bytes!!",0
boot2:
	mov esi,hello
	mov ebx,0xb8000 ; vga text buff location
.loop:
	lodsb
	or al,al
	jz halt
	or eax,0x0F00
	mov word [ebx], ax ; write char/short into buffer
	add ebx,2 ; vga text is short (2bytes). move to the next short.
	jmp .loop
halt:
	mov esp,kernel_stack_top ; setup kernel stack and enter into kernal
	extern kmain
	call kmain
	cli
	hlt

section .bss
align 4
kernel_stack_bottom: equ $
	resb 16384 ; 16 KB uninitialized data.
kernel_stack_top:
