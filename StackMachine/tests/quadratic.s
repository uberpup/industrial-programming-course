mov ax 1
mov bx 7
mov cx 4
cmp ax 0
je linear_case
jne quadratic_case

linear_case:
cmp bx 0
je const_case

const_case:
cmp cx 0
je infinite_roots
jne no_roots

quadratic_case:
mov dx bx
imul dx bx
mov di 4
imul di ax
imul di cx
sub dx di
cmp dx 0
jl no_roots
je one_root
jmp two_roots

no_roots:
mov dx 0
out dx
end

one_root:
sub dx bx
div dx 2
div dx ax
mov ax dx
mov dx 1
out dx
out ax
end

two_roots:
mov di 0
sub di bx
mov si di
sqrt dx
sub di dx
add si dx
mov cx 2
imul cx ax
div di cx
div si cx
mov dx 2
mov ax di
mov bx si
out dx
out ax
out bx
end

infinite_roots:
mov dx 3
out dx
end
