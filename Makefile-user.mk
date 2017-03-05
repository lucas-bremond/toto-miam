## Local build configuration
## Parameters configured here will override default and ENV values.
## Uncomment and change examples:

## Add your source directories here separated by space
MODULES = src
# EXTRA_INCDIR = include

## ESP_HOME sets the path where ESP tools and SDK are located.
## Windows:
# ESP_HOME = c:/Espressif

## MacOS / Linux:
# ESP_HOME = /opt/esp-open-sdk
ESP_HOME = ./thirdparty/esp-open-sdk

ESPTOOL2 = ./thirdparty/esptool2/esptool2

## SMING_HOME sets the path where Sming framework is located.
## Windows:
# SMING_HOME = c:/tools/sming/Sming 

## MacOS / Linux
# SMING_HOME = /opt/sming/Sming
SMING_HOME = ./thirdparty/Sming/Sming

## COM port parameter is reqruied to flash firmware correctly.
## Windows: 
# COM_PORT = COM3

## MacOS / Linux:
# COM_PORT = /dev/tty.usbserial
# COM_PORT = /dev/tty.SLAB_USBtoUART
# COM_PORT = /dev/tty.wchusbserialfd120
# COM_PORT = /dev/cu.wchusbserialfa130
COM_PORT = /dev/tty.wchusbserialfa130

# If serial not found: sudo easy_install pyserial

## Com port speed
# COM_SPEED	= 115200

## Configure flash parameters (for ESP12-E and other new boards):
# SPI_MODE = dio

## SPIFFS options
# DISABLE_SPIFFS = 1
# SPIFF_FILES = web/build
DISABLE_SPIFFS = 0
SPIFF_FILES = ./files

ENABLE_GDB = 0

SPI_SIZE = 4M
# COM_SPEED = 115200
# SPI_MODE = dio
