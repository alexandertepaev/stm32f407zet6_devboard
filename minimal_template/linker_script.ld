MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 128K /* Tehcnically 192KB, but the address space is not continuous 64KB kB in CCM RAM */ 
}

SECTIONS
{
    .text :
    {
        *(.vector_table)
        *(.text)            /* code */
    } >FLASH
}