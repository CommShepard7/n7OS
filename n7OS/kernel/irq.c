#include <inttypes.h>
#include <n7OS/irq.h>


void init_irq_entry(int irq_num, uint32_t addr) {
    idt_entry_t * idtEntry =  (idt_entry_t *) &idt[irq_num];
    idtEntry -> offset_inf = addr & 0x0000FFFF;
    idtEntry -> sel_segment = KERNEL_CS;
    idtEntry -> zero = 0;
    idtEntry -> type_attr = 0x8E;
    idtEntry -> offset_sup = (addr >> 16) & 0xFFFF;
}
