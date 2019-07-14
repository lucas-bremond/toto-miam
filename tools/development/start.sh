#!/usr/bin/env bash

################################################################################################################################################################

# @project        Toto|Miam
# @file           tools/development/start.sh
# @author         Lucas Brémond <lucas.bremond@gmail.com>
# @license        MIT License

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

# Load environment

source ".env"

# Start development environment

docker run \
--name=${container_name} \
-it \
--privileged \
--rm \
--volume="${project_directory}:/app" \
--device="${usb_device}:/dev/ttyUSB0" \
--workdir="/app/tools/development/helpers" \
"${image_name}:${image_version}"

popd > /dev/null

################################################################################################################################################################
