#!/bin/bash

env -i

tools_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
thirdparty_directory="${tools_directory}/../thirdparty"

${tools_directory}/clean.sh

export ESP_HOME="${thirdparty_directory}/esp-open-sdk"
export SMING_HOME="${thirdparty_directory}/Sming/Sming"

pushd "${tools_directory}/.."

make -j 8

popd