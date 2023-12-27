#include <stdio.h>
#include <ulib.h>
//第一个应用程序
int
main(void) {
    cprintf("Hello world!!.\n");
    //通过系统调用sys_getpid()获取pid
    cprintf("I am process %d.\n", getpid());
    cprintf("hello pass.\n");
    return 0;
}

