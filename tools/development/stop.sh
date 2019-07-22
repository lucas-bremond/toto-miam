#!/usr/bin/env bash

################################################################################################################################################################

# @project        Toto|Miam
# @file           tools/development/stop.sh
# @author         Lucas Brémond <lucas.bremond@gmail.com>
# @license        MIT License

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

# Load environment

source ".env"

# Stop development environment

docker rm -f ${container_name}

popd > /dev/null

################################################################################################################################################################
