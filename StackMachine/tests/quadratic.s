mov ax sp
mov bx 22
mov cx 6
cmp ax 0
je linear_case
cmp ax 0
jne quadratic_case

linear_case:
cmp bx 0
je const_case

const_case:
cmp cx 0
je infinite_roots
cmp cx 0
jne no_roots

quaratic_case:
mov dx bx
imul dx bx
push di
mov di 4
imul di ax
imul di cx
sub dx di
pop di
cmp dx 0
jl no_roots
cmp dx 0
je one_root
jmp two_roots

no_roots:
mov dx 0
end

one_root:
sub dx bx
div dx 2
div dx ax
mov ax dx
mov dx 1
end

two_roots:
push di
push si
mov di 0
sub di bx
mov si di
sqrt dx
sub di dx
add si dx
div di 2
div si 2
div di ax
div si ax
mov dx 2
mov ax di
mov bx si
pop si
pop di
end

infinite_roots:
mov dx 3
end
