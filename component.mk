################################################################################################################################################################

# @project        Toto|Miam
# @file           component.mk
# @author         Lucas Brémond <lucas.bremond@gmail.com>
# @license        MIT License

################################################################################################################################################################

## Application Component configuration
## Parameters configured here will override default and ENV values

## Add your source directories here separated by space

COMPONENT_INCDIRS := include
# COMPONENT_SRCDIRS := src/TotoMiam # Disabled, otherwise the build system fails
# COMPONENT_SRCFILES :=

## If you require any Arduino Libraries list them here

ARDUINO_LIBRARIES := ArduinoJson6

## List the names of any additional Components required for this project

# COMPONENT_DEPENDS :=

## Set paths for any GIT submodules your application uses

# COMPONENT_SUBMODULES :=

## Append any targets to be built as dependencies of the project, such as generation of additional binary files

# CUSTOM_TARGETS +=

## Additional object files to be included with the application library

# EXTRA_OBJ :=

## Additional libraries to be linked into the project

# EXTRA_LIBS :=

## Update any additional compiler flags

# CFLAGS +=
# CXXFLAGS +=

## Configure flash parameters (for ESP12-E and other new boards):

# SPI_MODE := dio
SPI_SIZE := 4M

## SPIFFS options

DISABLE_SPIFFS := 0
SPIFF_FILES := ./files

## Refer to Basic_rBoot sample for options relating to rBoot

# RBOOT_ENABLED=1

## ESP_HOME sets the path where ESP tools and SDK are located.

ESP_HOME := /opt/esp-open-sdk
ESPTOOL2 := /opt/esp-open-sdk/esptool2/esptool2

## SMING_HOME sets the path where Sming framework is located.

SMING_HOME := /opt/Sming/Sming

## COM port parameter is required to flash firmware correctly.

COM_PORT := /dev/ttyUSB0
COM_SPEED := 115200
# COM_OPTS := "--raw --encoding ascii" # Not working

################################################################################################################################################################
