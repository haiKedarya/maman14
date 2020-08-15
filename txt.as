MAIN: add r3,LIST
LOOP: .data 48
lea STR, r6
prn #48
inc r6
mov r3,K
sub r1,r4
STR: .string "abcd"
.extern W
