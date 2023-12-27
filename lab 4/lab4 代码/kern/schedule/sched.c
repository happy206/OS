#include <list.h>
#include <sync.h>
#include <proc.h>
#include <sched.h>
#include <assert.h>

void
wakeup_proc(struct proc_struct *proc) {
    assert(proc->state != PROC_ZOMBIE && proc->state != PROC_RUNNABLE);
    proc->state = PROC_RUNNABLE;
}

void
schedule(void) {
    bool intr_flag;
    list_entry_t *le, *last;
    struct proc_struct *next = NULL;
    //需要将调度操作原子化，不能被打断。因此要关闭中断。
    local_intr_save(intr_flag);
    {
        current->need_resched = 0;
        //idleproc的作用，就是当队列里没有就绪进程时，在cpu_idle函数中不断循环进入schedule（），不断搜索就绪态的进程
        last = (current == idleproc) ? &proc_list : &(current->list_link);
        le = last;
        do {
            if ((le = list_next(le)) != &proc_list) {
                next = le2proc(le, list_link);
                if (next->state == PROC_RUNNABLE) {
                    //如果有正在运行的process，就不找了
                    break;
                }
            }
        } while (le != last);
        if (next == NULL || next->state != PROC_RUNNABLE) {
            //如果找完之后，没有合适的进程，就继续让idleproc跑
            next = idleproc;
        }
        next->runs ++;//进程被调度的次数加一
        if (next != current) {
            //允许调度的条件是前后进程不能是同一个
            proc_run(next);
        }
    }
    local_intr_restore(intr_flag);
}

