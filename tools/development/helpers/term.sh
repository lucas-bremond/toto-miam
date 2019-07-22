#!/usr/bin/env bash

################################################################################################################################################################

# @project        Toto|Miam
# @file           tools/development/helpers/term.sh
# @author         Lucas Brémond <lucas.bremond@gmail.com>
# @license        MIT License

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
project_directory="${script_directory}/../../.."

pushd "${project_directory}" > /dev/null

# screen /dev/ttyUSB0 74880 # Exit: Ctrl-a Ctrl-\
# screen /dev/ttyUSB0 115200 # Exit: Ctrl-a Ctrl-\

# python -m serial.tools.miniterm /dev/ttyUSB0 74880
# python -m serial.tools.miniterm --raw --encoding ascii /dev/ttyUSB0 74880
python -m serial.tools.miniterm --raw --encoding ascii /dev/ttyUSB0 115200

popd > /dev/null

################################################################################################################################################################
