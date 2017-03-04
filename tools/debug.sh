#!/bin/bash

current_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

${current_directory}/../thirdparty/esp-open-sdk/xtensa-lx106-elf/bin/xtensa-lx106-elf-gdb -x ${current_directory}/gdbcmds -b 115200