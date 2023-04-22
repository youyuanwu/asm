find_program(qemu_exe
  NAMES qemu-system-x86_64.exe
  PATHS  "C:\\Program Files\\qemu"
  REQUIRED
)

# Get-FileHash -Algorithm SHA256 build/iso/vinix.iso
message(STATUS "fetching vinix")
set(VINIX_ISO "${CMAKE_CURRENT_BINARY_DIR}/iso/vinix.iso")
# fetch vinix iso
file(DOWNLOAD
  "https://github.com/vlang/vinix/releases/download/nightly-2022-07-16/vinix-nightly-20220716.iso"
  ${VINIX_ISO}
  SHOW_PROGRESS
  TIMEOUT 300
  EXPECTED_HASH  SHA256=B73483F1050334574357AF221980B35A3F07CB0960317A931036FF71091EFD7B
)

add_custom_target(run_vinix
  COMMAND start powershell -noexit -command "& '${qemu_exe}' -M q35,smm=off -m 8G -cdrom '${VINIX_ISO}' -serial stdio -smp 1"
)
