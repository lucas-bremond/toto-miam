# TotoMiam

ESP8266 firmware for TotoMiam.

Copyright (c) 2016 Lucas Brémond

For legal stuff, see LICENSE.

Citing the great Peter Andersson:
*Basically, you may do whatever you want with the source. Use, modify, sell, print it out, roll it and smoke it - as long as I won't be held responsible.*

## Description

TotoMiam is a wirelessly controlled automomous cat feeding system.

## Setup

### Configuration

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

### Build

```bash
make flash
```
