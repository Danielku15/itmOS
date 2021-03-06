////////////////////////////////////////////////////////
// Linker command file for BeagleBoard
// 
// Configuration of the BOSS-Project
//

-stack           0x00002000
-heap            0x00020000

MEMORY
{
   kernel_master_table: ORIGIN = 0x40200000 LENGTH = 0x00004000
   int_ram:  ORIGIN = 0x40204000  LENGTH = 0x0000BFC4
   int_vecs: ORIGIN = 0x4020FFC4  LENGTH = 0x0000003B
   
   ext_ddr:  ORIGIN = 0x82000000  LENGTH = 0x02000000 // 256 MBit
   
}

SECTIONS
{
///////////////////////////// int_ram //////////////////////////////
   .intvecs    > int_vecs {
   		_intvecsStart = .;
   		*(.intvecs)
   	}

   .kernelMasterTable > kernel_master_table {
       _kernelMasterTable = . ;
       . = . + (16 * 1024);
   }
   ORDER
   .cinit      > int_ram
   .data       > int_ram
   .far        > int_ram
   
   .stack      > int_ram
   .cio        > int_ram
   
   .switch     > int_ram
   .text2      > int_ram {
       Interrupts.obj
   }
   .pinit      > int_ram {
       *(.pinit)
        . = ALIGN(0x4);
        _swiParameterAddress = .;
        . = . + 128;
   		_intRamStart = .;
   	}


///////////////////////////// ext_ddr //////////////////////////////
ORDER

   .const      > ext_ddr
   .text	   > ext_ddr
   .sysmem     > ext_ddr
   .bss        > ext_ddr
   .stackArea  > ext_ddr {
       . = ALIGN(0x4);
       . = . + (4 * 1024);
       kernelStack = .;
	   . = . + (4 * 1024);
	   irqStack = .;
	   . = . + (4 * 1024);
	   systemStack = .;
	   . = . + (4 * 1024);
	   abortStack = .;
	   _extDDRStart = .;
   }
}
