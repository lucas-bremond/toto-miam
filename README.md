# Toto|Miam

## Description

Toto|Miam is a wirelessly controlled automomous cat feeding system.

## Hardware

[ESP8266 development board](https://www.aliexpress.com/item/New-Wireless-module-NodeMcu-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266-with-pcb-Antenna/32452167994.html?spm=2114.13010608.0.0.C43LjP)

## Firmware

### Setup

#### Configuration

Create a `./files/Setting.json` configuration file with the following content:

```json
{
    "network":
    {
        "ssid": "WIFI_SSID",
        "password": "WIFI_PASSWORD"
    }

}
```

#### Build

```bash
make
```

#### Flash

```bash
make flash
```

## Copyright

(c) 2016 Lucas Brémond

Citing Peter Andersson, author of the great [SPIFFS](https://github.com/pellepl/spiffs) library:

*For legal stuff, see LICENSE.*     
*Basically, you may do whatever you want with the source.*      
*Use, modify, sell, print it out, roll it and smoke it - as long as I won't be held responsible.*   
