# find_program(ml_exe
#   NAMES ml
#   #PATHS  "C:\\Program Files\\qemu"
#   REQUIRED
# )

# message(STATUS "Using ${ml_exe}")

# find_program(link_exe
#  NAMES link16
#  REQUIRED
# )

# message(STATUS "Using ${link_exe}")


# add_custom_target(build_boot ALL
#   DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/bootloader.bin
# )

# add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/bootloader.obj
#   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/bootloader.asm
#   COMMAND ${ml_exe} /nologo /AT /c ${CMAKE_CURRENT_SOURCE_DIR}/bootloader.asm
#   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
# )

# add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/bootloader.bin
#   COMMAND ${link_exe} /nologo /NOD ${CMAKE_CURRENT_BINARY_DIR}/bootloader.obj /OUT:${CMAKE_CURRENT_BINARY_DIR}/bootloader.bin /SUBSYSTEM:EFI_ROM
#   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#   DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/bootloader.obj
# )

# qemu-system-i386 -fda boot.bin

#############
#set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
#set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
# set(CMAKE_ASM_NASM_OBJECT_FORMAT bin)

# project(test_project C ASM_NASM)

# set_source_files_properties(bootloader.asm PROPERTIES LANGUAGE ASM_NASM)
# add_executable(bootloader.bin bootloader.asm)
# #target_compile_options(bootloader.bin PRIVATE -fbin)
# # if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# #     target_compile_options(test PRIVATE -g -Fdwarf)
# # endif()
# target_link_options(bootloader.bin PUBLIC /SUBSYSTEM:EFI_ROM)
##############
#

project(test_project ASM_NASM)
message(STATUS "Found NASM exe: ${CMAKE_ASM_NASM_COMPILER}")

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/bootloader.bin
  COMMAND ${CMAKE_ASM_NASM_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/bootloader.asm -f bin -o bootloader.bin
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/bootloader.asm
)

add_custom_target(build_boot ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/bootloader.bin
)


find_program(qemu_i386_exe
  NAMES qemu-system-i386.exe
  PATHS  "C:\\Program Files\\qemu"
  REQUIRED
)

add_custom_target(run_boot
  COMMAND start powershell -noexit -command "& '${qemu_i386_exe}' -drive format=raw,file=${CMAKE_CURRENT_BINARY_DIR}/bootloader.bin"
)



