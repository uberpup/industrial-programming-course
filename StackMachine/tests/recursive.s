mov ax 1
mov bx 1
mov cx 6
mod dx cx
jmp factorial

factorial:
cmp cx bx
push ax
ret
je exit
mul cx
sub cx 1
call factorial

exit:
out
end