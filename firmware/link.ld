OUTPUT_ARCH(m68k)

MEMORY {
    /* TODO: Document */
    startup (rx) : ORIGIN = 0x00, LENGTH = 0x400
    rom (rx) : ORIGIN = 0x400, LENGTH = 0x7FC00
    ram (rwx) : ORIGIN = 0x80000, LENGTH = 0x20000
}

/* Place stack at the top of RAM. */
PROVIDE (__stack = 0xA0000);

SECTIONS {
    /* 
     * Interrupt vectors should be placed at the beginning of ROM, allowing
     * them to be modified during runtime. 
     */
    . = 0x0;
    .vectors : {
        *(.vectors);
    } >startup

    /* Origin of ROM */
    . = 0x400;
    
    .text : {
        *(.text);
    } >rom

    .rodata : {
        *(.rodata);
    } >rom

    . = ALIGN(4);
    _rom_end = .;

    /* RAM Sections */
    . = 0x80000;

    .data ALIGN(4) : {
        _data_start = .;
        *(.data);
        . = ALIGN(4);
        _data_end = .;
    } >ram 
    _data_size = SIZEOF(.data);

    .bss ALIGN(4) : {
        _bss_start = .;
        *(.bss);
        . = ALIGN(4);
        _bss_end = .;
    } >ram
    _bss_size = SIZEOF(.bss);
    
    . = ALIGN(4);
    _ram_end = .;
}
