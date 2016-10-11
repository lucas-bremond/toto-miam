#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

${DIR}/../thirdparty/esp-open-sdk/xtensa-lx106-elf/bin/xtensa-lx106-elf-gdb -x ${DIR}/gdbcmds -b 115200