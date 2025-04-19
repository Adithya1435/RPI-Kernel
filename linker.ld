ENTRY(_start)

MEMORY {
    RAM : ORIGIN = 0x8000, LENGTH = 128M
    USER_RAM : ORIGIN = 0x400000, LENGTH = 64M
}

SECTIONS {
    . = 0x8000;
    __start = .;

    __text_start = .;
    .text : {
        KEEP(*(.text.boot))
        *(.text)
    }
    . = ALIGN(4096);
    __text_end = .;

    __data_start = .;
    .data : {
        *(.data)
    }
    . = ALIGN(4096);
    __data_end = .;

    __bss_start = .;
    .bss : {
        *(.bss)
    }
    . = ALIGN(4096);
    __bss_end = .;
    __end = .;

    /* User space */
    . = 0x400000;
    __user_start = .;
    .user.text : {
        user_space/user.o(.text)
    } > USER_RAM
    .user.data : {
        user_space/user.o(.data)
    } > USER_RAM
    .user.bss : {
        user_space/user.o(.bss)
    } > USER_RAM
    __user_end = .;
}
