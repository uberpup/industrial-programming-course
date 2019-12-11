mov ax 1
mov bx 1
mov cx 33
mod dx cx
jmp factorial

factorial:
cmp cx bx
je exit
mul cx
sub cx 1
jmp factorial

exit:
out ax
end