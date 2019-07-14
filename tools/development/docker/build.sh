#!/usr/bin/env bash

################################################################################################################################################################

# @project        Toto|Miam
# @file           tools/development/docker/build.sh
# @author         Lucas Brémond <lucas.bremond@gmail.com>
# @license        MIT License

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

# Load environment

source "../.env"

# Build Docker image

docker build \
--tag="${image_name}:${image_version}" \
--file="Dockerfile" \
.

popd > /dev/null

################################################################################################################################################################
