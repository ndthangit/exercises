# Th?c hành l?nh logic (BaiTH_03.asm)

lui $s0, 0xAAAA

ori $s0, $s0, 0xAAAA
lui $s1, 0xFFFF
and $s3, $s0, $s1
or $s4, $s0, $s1
xor $s5, $s0, $s1
nor $s6, $s0, $s1

sll $t0, $s0, 4
srl $t1, $s0, 4
sll $t2, $s0, 3
srl $t3, $s0, 3
sll $t4, $s0, 2
srl $t5, $s0, 2
Sll $t6, $t0, 5
srl $t7, $s0, 5
