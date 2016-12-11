#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# ${DIR}/../thirdparty/esp-open-sdk/esptool/esptool.py --port /dev/tty.SLAB_USBtoUART erase_flash

(cd ${DIR}/.. && make flashinit)