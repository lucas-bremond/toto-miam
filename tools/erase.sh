#!/bin/bash

env -i

tools_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
thirdparty_directory="${tools_directory}/../thirdparty"

export ESP_HOME="${thirdparty_directory}/esp-open-sdk"
export SMING_HOME="${thirdparty_directory}/Sming/Sming"

pushd "${tools_directory}/.."

# ${tools_directory}/../thirdparty/esp-open-sdk/esptool/esptool.py --port /dev/tty.SLAB_USBtoUART erase_flash

make flashinit

popd