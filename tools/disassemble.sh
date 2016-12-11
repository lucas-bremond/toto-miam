#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

${DIR}/../thirdparty/esp-open-sdk/xtensa-lx106-elf/xtensa-lx106-elf/bin/objdump -d ${DIR}/../out/build/app.out >disassemble.txt