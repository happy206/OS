.text
.globl _start#所有应用程序的起始用户态执行地址，调用EBP和ESP后调用umain函数
_start:
    # call user-program function
    call umain
1:  j 1b
