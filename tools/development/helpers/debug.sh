#!/usr/bin/env bash

################################################################################################################################################################

# @project        Toto|Miam
# @file           tools/development/helpers/debug.sh
# @author         Lucas Brémond <lucas.bremond@gmail.com>
# @license        MIT License

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

/opt/esp-open-sdk/xtensa-lx106-elf/bin/xtensa-lx106-elf-gdb -x ${script_directory}/gdbcmds -b 115200 # [TBM] Probably not working anymore

################################################################################################################################################################
