cmake_minimum_required(VERSION 3.18.0)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/section_map.ld") 
project(shit_OS)
enable_language(ASM_NASM)
add_subdirectory(kernel/libk)

include_directories("kernel/libk/include")

file(GLOB ASM_SOURCE "kernel/*.asm")
set_source_files_properties(${ASM_SOURCE} PROPERTIES LANGUAGE ASM_NASM)
add_executable(${PROJECT_NAME}.bin
    kernel/main.cpp
    ${ASM_SOURCE}
)
set_target_properties(${PROJECT_NAME}.bin PROPERTIES LINK_FLAGS "-nostdlib -T ${LINKER_SCRIPT}")
target_link_libraries(${PROJECT_NAME}.bin k)

install(DIRECTORY DESTINATION iso/boot/grub)
install(FILES grub.cfg DESTINATION iso/boot/grub)
install(TARGETS ${PROJECT_NAME}.bin DESTINATION iso/boot)
install(CODE "
exec_program(grub-file ${CMAKE_CURRENT_SOURCE_DIR} ARGS \"--is-x86-multiboot iso/boot/${PROJECT_NAME}.bin\" RETURN_VALUE IS_MULTIBOOT)
if(IS_MULTIBOOT)
    message(\"Grub don't recognize multiboot\")
    else()
        message(\"Multiboot is OK\")
        exec_program(grub-mkrescue ${CMAKE_CURRENT_SOURCE_DIR} ARGS \"iso -o ${PROJECT_NAME}.iso\")
endif(IS_MULTIBOOT)")
