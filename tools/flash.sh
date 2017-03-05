#!/bin/bash

current_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

${current_directory}/clean.sh

(cd ${current_directory}/.. && make -j 8 flash)
