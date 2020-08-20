.entry LIST
.entry YOSSI
 .extern W
MAIN:            add r3, LIST
lea    W, r6
inc       r6
mov     r3,K 
sub   r1, r4
bne   END
bne    &END
dec W
.entry MAIN
jmp    &LOOP
add   L3, L3
END:   stop
STR:             .string  "abcd"
LIST: .data   6, -9, -8,20,103
K: .data   31
.extern L3
