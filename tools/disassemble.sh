#!/bin/bash

current_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

${current_directory}/../thirdparty/esp-open-sdk/xtensa-lx106-elf/xtensa-lx106-elf/bin/objdump -d ${current_directory}/../out/build/app.out >disassemble.txt