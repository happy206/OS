/* Simple linker script for the ucore kernel.
   See the GNU ld 'info' manual ("info ld") to learn the syntax. */

OUTPUT_ARCH(riscv)
ENTRY(kern_entry)

BASE_ADDRESS = 0xFFFFFFFFC0200000;

SECTIONS
{
    /* Load the kernel at this address: "." means the current address */
    /*描述了操作系统的内核虚拟空间的起始入口虚拟地址：BASE_ADDRESS = 0xFFFFFFFFC0200000*/
    . = BASE_ADDRESS;

    .text : {
        *(.text.kern_entry .text .stub .text.* .gnu.linkonce.t.*)
    }

    PROVIDE(etext = .); /* Define the 'etext' symbol to this value */

    .rodata : {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
    }

    /* Adjust the address for the data segment to the next page */
    . = ALIGN(0x1000);

    /* The data segment */
    .data : {
        *(.data)
        *(.data.*)
    }

    .sdata : {
        *(.sdata)
        *(.sdata.*)
    }

    PROVIDE(edata = .);

    .bss : {
        *(.bss)
        *(.bss.*)
        *(.sbss*)
    }

    PROVIDE(end = .);

    /DISCARD/ : {
        *(.eh_frame .note.GNU-stack)
    }
}
