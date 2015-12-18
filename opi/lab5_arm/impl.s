.global impl

impl:
mov ip, 0
str ip, [r3]

smull r0,ip,r0,r1
cmp ip, r0, ASR #31
bne mul_overflow
b substraction

mul_overflow:
mov ip, 1
str ip, [r3]
b substraction

substraction:
sub r0,r0,r2
bvs  sub_overflow
str ip, [r3]
bx lr

sub_overflow:
mov ip,#42
str ip, [r3]
bx lr
