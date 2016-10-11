#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

${DIR}/clean.sh

(cd ${DIR}/.. && make flash)