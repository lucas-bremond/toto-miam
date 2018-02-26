#!/bin/bash

# https://github.com/SmingHub/Sming/wiki/MacOS-Quickstart

env -i

thirdparty_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# xcode-select --install

# brew install binutils coreutils automake wget gawk libtool gettext gperf grep

# export PATH="/usr/local/opt/gnu-sed/libexec/gnubin:$PATH"

# brew install gnu-sed --with-default-names

mkdir -p "${thirdparty_directory}"

pushd "${thirdparty_directory}"

curl -L -O  https://dl.bintray.com/sminghub/toolchain/esp-open-sdk-2.0-macosx.tgz
tar -zxf esp-open-sdk-2.0-macosx.tgz -C "${thirdparty_directory}"
chmod -R 775 "${thirdparty_directory}/esp-open-sdk"
rm "${thirdparty_directory}/esp-open-sdk-2.0-macosx.tgz"

git clone https://github.com/SmingHub/Sming.git

cd "${thirdparty_directory}/Sming/Sming"

export ESP_HOME="${thirdparty_directory}/esp-open-sdk"
export SMING_HOME="${thirdparty_directory}/Sming/Sming"

make

sudo pip install pyserial

# export COM_PORT="/dev/tty.wchusbserial40110"