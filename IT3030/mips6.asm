Loop: sll $t1, $s3, 2 # $t1 = 4*i 
add $t1, $t1, $s6 # $t1 = ??a ch? A[i]
lw $t0, 0($t1) # $t0 = A[i]
bne $t0, $s5, Exit # n?u A[i]!=k thì Exit
addi $s3, $s3, 1 # n?u A[i]=k thì i=i+1
j Loop # quay l?i Loop
Exit: ..