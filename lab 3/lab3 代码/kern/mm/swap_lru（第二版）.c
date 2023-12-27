#include <defs.h>
#include <riscv.h>
#include <stdio.h>
#include <string.h>
#include <swap.h>
#include <swap_lru.h>
#include <list.h>
#include <pmm.h>


list_entry_t pra_list_head;
list_entry_t* curr_ptr;


static int
_lru_init_mm(struct mm_struct* mm)
{
    list_init(&pra_list_head);
    mm->sm_priv = &pra_list_head;
    return 0;
}

static int
_lru_map_swappable(struct mm_struct* mm, uintptr_t addr, struct Page* page, int swap_in)
{

    list_entry_t* head = (list_entry_t*)mm->sm_priv;
    list_entry_t* entry = &(page->pra_page_link);
    assert(entry != NULL && head != NULL);
    curr_ptr = head->next;
    while (curr_ptr != head) {
        if (curr_ptr == entry) {
            list_del(entry);
            break;
        }
        curr_ptr = curr_ptr->next;
    }
    list_add(head, entry);
    return 0;
}


static int
_lru_swap_out_victim(struct mm_struct* mm, struct Page** ptr_page, int in_tick)
{
    list_entry_t* head = (list_entry_t*)mm->sm_priv;
    assert(head != NULL);
    assert(in_tick == 0);
    list_entry_t* entry = list_prev(head);
    if (entry != head) {
        list_del(entry);
        *ptr_page = le2page(entry, pra_page_link);
    }
    else {
        *ptr_page = NULL;
    }
    return 0;
}

static int
_lru_update(struct mm_struct* mm, uintptr_t addr) {
    pte_t* ptep = NULL;
    ptep = get_pte(mm->pgdir, addr, 1);
    if (ptep == NULL) {

    }
    else {
        _lru_map_swappable(mm, addr, pte2page(*ptep), 0);
    }
    return 0;
}

static int
_lru_check_swap(void) {

    cprintf("---------LRU check begin----------\n");
    cprintf("write Virt Page 3 in lru_check_swap\n");
    *(unsigned char*)0x3000 = 0x0c;
    _lru_update(check_mm_struct, 0x3000);
    assert(pgfault_num == 4);
    cprintf("write Virt Page 1 in lru_check_swap\n");
    *(unsigned char*)0x1000 = 0x0a;
    _lru_update(check_mm_struct, 0x1000);
    assert(pgfault_num == 4);
    cprintf("write Virt Page 4 in lru_check_swap\n");
    *(unsigned char*)0x4000 = 0x0d;
    _lru_update(check_mm_struct, 0x4000);
    assert(pgfault_num == 4);
    cprintf("write Virt Page 2 in lru_check_swap\n");
    *(unsigned char*)0x2000 = 0x0b;
    _lru_update(check_mm_struct, 0x2000);
    assert(pgfault_num == 4);
    cprintf("write Virt Page 5 in lru_check_swap\n");
    *(unsigned char*)0x5000 = 0x0e;
    _lru_update(check_mm_struct, 0x5000);
    assert(pgfault_num == 5);
    cprintf("write Virt Page 3 in lru_check_swap\n");
    *(unsigned char*)0x3000 = 0x0c;
    _lru_update(check_mm_struct, 0x3000);
    assert(pgfault_num == 6);
    cprintf("write Virt Page 1 in lru_check_swap\n");
    *(unsigned char*)0x1000 = 0x0a;
    _lru_update(check_mm_struct, 0x1000);
    assert(pgfault_num == 7);
    cprintf("write Virt Page b in fifo_check_swap\n");
    *(unsigned char*)0x2000 = 0x0b;
    _lru_update(check_mm_struct, 0x2000);
    assert(pgfault_num == 7);
    cprintf("write Virt Page c in fifo_check_swap\n");
    *(unsigned char*)0x3000 = 0x0c;
    _lru_update(check_mm_struct, 0x3000);
    assert(pgfault_num == 7);
    cprintf("write Virt Page d in fifo_check_swap\n");
    *(unsigned char*)0x4000 = 0x0d;
    _lru_update(check_mm_struct, 0x4000);
    assert(pgfault_num == 8);
    cprintf("write Virt Page e in fifo_check_swap\n");
    *(unsigned char*)0x5000 = 0x0e;
    _lru_update(check_mm_struct, 0x5000);
    assert(pgfault_num == 9);
    cprintf("write Virt Page a in fifo_check_swap\n");
    *(unsigned char*)0x1000 = 0x0a;
    _lru_update(check_mm_struct, 0x1000);
    assert(pgfault_num == 10);
    cprintf("LRU check succeed!\n");

    return 0;
}


static int
_lru_init(void)
{
    return 0;
}

static int
_lru_set_unswappable(struct mm_struct* mm, uintptr_t addr)
{
    return 0;
}

static int
_lru_tick_event(struct mm_struct* mm)
{
    return 0;
}


struct swap_manager swap_manager_lru =
{
     .name = "lru swap manager",
     .init = &_lru_init,
     .init_mm = &_lru_init_mm,
     .tick_event = &_lru_tick_event,
     .map_swappable = &_lru_map_swappable,
     .set_unswappable = &_lru_set_unswappable,
     .swap_out_victim = &_lru_swap_out_victim,
     .check_swap = &_lru_check_swap,
};