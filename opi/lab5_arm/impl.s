.global impl

impl:
mov ip, 0
str ip, [r3]

mul r0, r0, r1

subs r0,r0,r2
bvs  sub_overflow
str ip, [r3]
bx lr

sub_overflow:
mov ip,#1
str ip, [r3]
bx lr
