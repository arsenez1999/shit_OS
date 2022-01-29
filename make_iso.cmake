exec_program(grub-file ${CMAKE_CURRENT_SOURCE_DIR} ARGS "--is-x86-multiboot iso/boot/${PROJECT_NAME}.bin" RETURN_VALUE IS_MULTIBOOT)
if(IS_MULTIBOOT)
    message("Grub don't recognize multiboot")
    else()
        message("Multiboot is OK")
        exec_program(grub-mkrescue ${CMAKE_CURRENT_SOURCE_DIR} ARGS "iso -o ${PROJECT_NAME}.iso")
endif(IS_MULTIBOOT)