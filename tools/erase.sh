#!/bin/bash

current_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# ${current_directory}/../thirdparty/esp-open-sdk/esptool/esptool.py --port /dev/tty.SLAB_USBtoUART erase_flash

(cd ${current_directory}/.. && make flashinit)