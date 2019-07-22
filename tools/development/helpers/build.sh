#!/usr/bin/env bash

################################################################################################################################################################

# @project        Toto|Miam
# @file           tools/development/helpers/build.sh
# @author         Lucas Brémond <lucas.bremond@gmail.com>
# @license        MIT License

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
project_directory="${script_directory}/../../.."

pushd "${project_directory}" > /dev/null

numproc=$(grep -c ^processor /proc/cpuinfo 2>/dev/null || 1)

make -j ${numproc}

popd > /dev/null

################################################################################################################################################################
