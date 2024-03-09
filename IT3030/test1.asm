.data # Define the data section
msg: .asciiz "hello world\n" # Define a string with a newline character

.text # Define the text section
main: # The main program
    li $v0, 4 # Load 4 into $v0 to indicate a print string system call
    la $a0, msg # Load the address of the string into $a0
    syscall # Invoke the system call
    li $v0, 10 # Load 10 into $v0 to indicate a exit system call
    syscall # Invoke the system call
