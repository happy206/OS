#include <riscv.h>

# 指示接下来的代码段是代码段
.text
# void switch_to(struct proc_struct* from, struct proc_struct* to)
# 标识 switch_to 函数是一个全局函数
.globl switch_to
# 汇编标签，表示接下来的代码是 switch_to 函数的实现
# a0和a1表示参数传递寄存器
switch_to:
    # save from's registers
    # 在<riscv.h>中 STORE 宏定义为 sd  LOAD 宏定义为 ld
    # REGBYTES在<riscv.h>中宏定义
    STORE ra, 0*REGBYTES(a0)
    STORE sp, 1*REGBYTES(a0)
    STORE s0, 2*REGBYTES(a0)
    STORE s1, 3*REGBYTES(a0)
    # s2寄存器的值将被存储在从 a0 寄存器指向的内存地址开始的第32字节处。
    STORE s2, 4*REGBYTES(a0)
    STORE s3, 5*REGBYTES(a0)
    STORE s4, 6*REGBYTES(a0)
    STORE s5, 7*REGBYTES(a0)
    STORE s6, 8*REGBYTES(a0)
    STORE s7, 9*REGBYTES(a0)
    STORE s8, 10*REGBYTES(a0)
    STORE s9, 11*REGBYTES(a0)
    STORE s10, 12*REGBYTES(a0)
    STORE s11, 13*REGBYTES(a0)

    # restore to's registers
    LOAD ra, 0*REGBYTES(a1)
    LOAD sp, 1*REGBYTES(a1)
    LOAD s0, 2*REGBYTES(a1)
    LOAD s1, 3*REGBYTES(a1)
    LOAD s2, 4*REGBYTES(a1)
    LOAD s3, 5*REGBYTES(a1)
    LOAD s4, 6*REGBYTES(a1)
    # s5寄存器将被加载从 a1 寄存器指向的内存地址开始的第56字节处的数据。
    LOAD s5, 7*REGBYTES(a1)
    LOAD s6, 8*REGBYTES(a1)
    LOAD s7, 9*REGBYTES(a1)
    LOAD s8, 10*REGBYTES(a1)
    LOAD s9, 11*REGBYTES(a1)
    LOAD s10, 12*REGBYTES(a1)
    LOAD s11, 13*REGBYTES(a1)
    # 用于从函数中返回，将控制返回到调用函数的位置
    ret
