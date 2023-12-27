.text
.globl kernel_thread_entry
kernel_thread_entry:        # void kernel_thread(void)
	move a0, s1				#kernel_thread的参数s1
	jalr s0					#跳转到kern_thread函数当中，函数指针保存在s0

	jal do_exit				#结束并释放相关资源
