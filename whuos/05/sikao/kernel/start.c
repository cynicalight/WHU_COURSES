
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            start.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "global.h"


/*======================================================================*
                            cstart
 *======================================================================*/
PUBLIC void cstart()
{
	disp_str("-----\"cstart\" begins-----");

	/* 将 LOADER 中的 GDT 复制到新的 GDT 中 */
	memcpy(&gdt,				  /* New GDT */
	       (void*)(*((u32*)(&gdt_ptr[2]))),   /* Base  of Old GDT */
	       *((u16*)(&gdt_ptr[0])) + 1	  /* Limit of Old GDT */
		);
	/* gdt_ptr[6] 共 6 个字节：0~15:Limit  16~47:Base。用作 sgdt/lgdt 的参数。*/
	u16* p_gdt_limit = (u16*)(&gdt_ptr[0]);
	u32* p_gdt_base  = (u32*)(&gdt_ptr[2]);
	*p_gdt_limit = GDT_SIZE * sizeof(DESCRIPTOR) - 1;
	*p_gdt_base  = (u32)&gdt;

	/* idt_ptr[6] 共 6 个字节：0~15:Limit  16~47:Base。用作 sidt/lidt 的参数。*/
	u16* p_idt_limit = (u16*)(&idt_ptr[0]);
	u32* p_idt_base  = (u32*)(&idt_ptr[2]);
	*p_idt_limit = IDT_SIZE * sizeof(GATE) - 1;
	*p_idt_base  = (u32)&idt;
	// MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
	init_prot();
	disp_str2("NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\nNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\nNNNNNNNNNNNNNNNNNNNNNNNNNXKNNXXXNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\nNNNNNNNNNNNNNNNXKNNNKNNNNKNXNXXXNNNNNNNNNNNNNNNNNNNNNNNNN0NNNXNXKNNNNN\nNNNNNNNNNNNNNKXXWNWNNKXNNNNNNNNNNNNNNNNNNNNN0xdcclcokXNNKXWNNWNKNNNNNN\nNNNNNNNNNNNNNNNXXNXXXNNNNNNNNNNNKkxxoloodx;'l0XWMMMXd cNNNXXXXXNNNNNNN\nNNNNNNNNNNXOxdxOXNNNNNNKxlcclloNdk00XNNNX0NMMMMMMMW0c dNNNNNNNNNNNNNNN\nNNNNNNNNX; d0K0xc, lK:.cokNMMMMMMMMMMMMMMMMMMMMW00K',oXNNNNNNKXNXNXNNNN\nNNNNNNNN.NMMMMMMMMKkWMMMMMMMMMMMMMMMMMMMMM0';cx0X0Oo', xNNNXXXXXKXNNNN\nNNNNNNNNKl::coolxMMMMMMMMWkKMk, , OMMWoONXXWMK..kMMMMMMMK'.ONNNNNNNNNNNN\nNNNNNNXXNNNNNXNN0clWMMMNXXKWMW' cxkxoc:lWMMMW0NMMMMMMMMN .NNNNNNNNNNNN\nNNNNKKNNXXKNNNNN, 0MMMMMKccllcdXNXKXNMMMMMMMMMMMMMMMMMX, .kNNNNNNNNNNNN\nNNNNXXXNXXNNNNNNX : dMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN. : NNNNNNNNNNNNNN\nNNNNNNNNNNNNNKOxl : xWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMK.lNNNNNNNNNNNNNN\nNNNNNNNNNk : ; : ok0XMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMX.NNNNNNNNNNNNN\nNNNNNNNN0.oMMMMMMMMWWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMX'.ONNNKK0kdkNN\nNNNNNNNNNNoc : odccOWc xMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMW.O, ;odd:..0N\nNNNNNNNNNNNNNKKNNNNN.KMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM, KXo:: : dKNNN\nNNNNNNNNNNNNNNNNNNNNo lMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM : kXNNNNNNNN\nNNNNNNNNNNNNNNNNNNNNNldMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN.NNNNNNNNN\n");
	disp_str("-----\"cstart\" ends-----\n");
	page_manage();
}
