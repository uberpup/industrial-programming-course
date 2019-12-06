mov ax 1
mov bx 0
mov cx sp
mod dx cx
jmp factorial

factorial:
cmp dx bx
je end
mul cx
sub cx 1
add bx 1
jmp factorial
