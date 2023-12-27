#include <ulib.h>

int main(void);

void
umain(void) {
    //调用应用程序的main函数，并在main函数结束后调用exit
    int ret = main();
    //exit内使用sys_exit让操作系统回收进程资源
    exit(ret);
}

