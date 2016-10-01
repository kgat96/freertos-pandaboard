/* Standard includes. */
#include <stdlib.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "mux.h"

struct omap_sys_ctrl_regs const **ctrl =
    (struct omap_sys_ctrl_regs const **)OMAP_SRAM_SCRATCH_SYS_CTRL;


void do_set_mux(u32 base, struct pad_conf_entry const *array, int size)
{
    int i;
    struct pad_conf_entry *pad = (struct pad_conf_entry *) array;

    for (i = 0; i < size; i++, pad++)
        writew(pad->val, base + pad->offset);
}


void set_muxconf_regs_non_essential(void)
{
    do_set_mux((*ctrl)->control_padconf_core_base,
            core_padconf_array_non_essential,
            sizeof(core_padconf_array_non_essential)
                    / sizeof(struct pad_conf_entry));

    do_set_mux((*ctrl)->control_padconf_core_base,
            core_padconf_array_non_essential_4460,
            sizeof(core_padconf_array_non_essential_4460)
                    / sizeof(struct pad_conf_entry));

    do_set_mux((*ctrl)->control_padconf_wkup_base,
            wkup_padconf_array_non_essential,
            sizeof(wkup_padconf_array_non_essential)
                    / sizeof(struct pad_conf_entry));

}


void kputc(char c)
{
    volatile unsigned int *lsr = (unsigned int *) 0x48020014;
    volatile unsigned int *thr = (unsigned int *) 0x48020000;

    if (c == '\n') {
        while (!(*lsr & 0x20));
        *thr = '\r';
    }

    while (!(*lsr & 0x20));
    *thr = c;
}

void kputhex(unsigned int value, int digits)
{
    while (digits-- > 0) {
        unsigned int tmp = (value >> (4 * digits)) & 0xf;
        kputc(tmp > 9 ? tmp - 10 + 'a' : tmp + '0');
    }
}

void kputs(char *s)
{
    while (*s) {
        kputc(*s++);
    }
}


void mgpio_set(void)
{
    static int led = 0;

    led = !led;

    writel(0xffffbfff, 0x48059134);  // set gpioC-14 110 output io

    if (led) {
        asm volatile ("nop\n\t"
                "ldr r2, =0x4000\n\t");
    } else {
        asm volatile ("nop\n\t"
                "ldr r2, =0xffffbfff\n\t");
    }

    asm volatile ("nop\n\t"
            "ldr r3, =0x4805913C\n\t"
            "str r2, [r3, #0]\n\t");

    asm volatile (
            "ldr r2, =0x48020014\n\t"
            "__mgpio_set_l2:\n\t"
            "ldr r3, [r2, #0]\n\t"
            "and.w  r3, r3, #0x20\n\t"
            "cmp r3, #0\n\t"
            "beq.n   __mgpio_set_l2\n\t"
            "mov r2, '#'\n\t"
            "ldr r3, =0x48020000\n\t"
            "str r2, [r3, #0]\n\t"
    );
}

/* enable IRQ interrupts */
void enable_interrupts (void)
{
    unsigned long temp;
    __asm__ __volatile__("mrs %0, cpsr\n"
                 "bic %0, %0, #0x80\n"
                 "msr cpsr_c, %0"
                 : "=r" (temp)
                 :
                 : "memory");
}

void core_info(int t)
{
    register volatile int tmp asm ("r2") = 1;

    //mcr p15, 0, r0, c12, c0, 0  @Set VBAR
    kputs("\nVBAR:");
    asm volatile ("MRC p15, 0, r2, c12, c0, 0");  // read VBAR
    kputhex(tmp, 8);

    kputs("\nSCTLR:");
    asm volatile ("MRC p15, 0, r2, c1, c0, 0 ");  // Read SCTLR into Rt
    kputhex(tmp, 8);


//    {
//        unsigned long temp;
//        __asm__ __volatile__("mrs %0, cpsr\n"
//                     "bic %0, %0, #0x80\n"
//                     "msr cpsr, %0"
//                     : "=r" (temp)
//                     :
//                     : "memory");
//    }

    kputs("\ncpsr:");
    asm volatile ("mrs  r2, cpsr");  // Read cpsr into Rt
    kputhex(tmp, 8);

}


void _init(void)
{
    kputc('A');
    kputs("_init\n");

    core_info(0);

    enable_interrupts();

    {
        #define TIME_OUT 0x1fffff
        volatile u32 i;

        u32 itlinesnr;

        set_muxconf_regs_non_essential();

        writel(0x20000, 0x4805914C); // Falling edge detection enabled
        writel(0x20000, 0x4805902C); // Status for interrupt line 0
        writel(0x20000, 0x48059034); // Status raw for interrupt line 0

#define GICADDRBASE 0x48241000
#define ICCADDRBASE 0x48240100

        /* enable the GIC distributor
         * Global enable for forwarding pending Group 0 interrupts
         * from the Distributor to the CPU interfaces GICD_CTLR */
        writel(readl(GICADDRBASE + GICD_CTLR) | 0x03,
                GICADDRBASE + GICD_CTLR);

        /* TYPER[4:0] contains an encoded number of available interrupts */
        itlinesnr = readl(GICADDRBASE + GICD_TYPER) & 0x1f;

        kputs("\nitlinesnr:");
        kputhex(readl(GICADDRBASE + GICD_TYPER), 8);

        /* set all bits in the GIC group registers to one to allow access
         * from non-secure state. The first 32 interrupts are private per
         * CPU and will be set later when enabling the GIC for each core
         */
        for (i = 1; i <= itlinesnr; i++)
            writel((unsigned)-1, GICADDRBASE + GICD_IGROUPRn + 4 * i);

        writel(1, GICADDRBASE + GICD_ITARGETSRn + 4 * 16);

        writel(1, GICADDRBASE + GICD_ISENABLERn + 4 * 2);

        writel(0xffff, ICCADDRBASE + GICC_PMR);

        writel(0xb, ICCADDRBASE + GICC_CTLR);

        kputs("\npanding:");
        kputhex(readl(GICADDRBASE + GICD_ISPENDRn + 8), 8);

        kputs("\nISENABLER:");
        kputhex(readl(GICADDRBASE + GICD_ISENABLERn + 8), 8);


        while(1) {
            mgpio_set();
            i = TIME_OUT;
            while (i--) ;


            kputs("\nirq:");
            kputhex(readl(0x4805902c), 8);
            kputs("\nind:");
            kputhex(readl(0x48059138), 8);

            kputs("\npanding:");
            kputhex(readl(GICADDRBASE + GICD_ISPENDRn + 8), 8);

            kputs("\nActive:");
            kputhex(readl(GICADDRBASE + GICD_ISACTIVERn + 8), 8);

            //core_info(0);

            writel(0x20000, 0x4805902C);


        }

    }


}


int _main(void)
{
    kputc('$');
    kputs("xxxinit\n");





    return 0;
}

__attribute__((naked)) void irq_handler(void)
{

    asm volatile (
            "SUB    SP, SP, #4 \n\t"
            "STMFD  sp!, {r0 - r3, r12, r14}\n\t"
            );

    kputc('F');
    writel(0x20000, 0x4805902C);

    asm volatile (
            "LDMFD  sp!, {r0 - r3, r12, r14}\n\t"
            "SUBS   PC, LR, #4 "
            );

    //while(1);
}

__attribute__((naked)) void fiq_handler(void)
{
    kputc('Q');
    while(1);
}


