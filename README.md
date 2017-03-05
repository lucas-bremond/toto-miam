# Toto|Miam

## Description

A wirelessly controlled automatic cat feeding system.

## Hardware

### Parts

#### Microcontroller

[WEMOS D1 mini](https://www.aliexpress.com/item/D1-mini-Mini-NodeMcu-4M-bytes-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266/32529101036.html?spm=2114.13010608.0.0.HZtg9v)

#### Actuator

Stepper Motor:

[28BYJ-48](https://www.aliexpress.com/item/5V-Stepper-Motor-28BYJ-48-With-Drive-Test-Module-Board-ULN2003-5-Line-4-Phase/32608569300.html?spm=2114.13010608.0.0.HZtg9v)

Drive Module Board:

[ULN2003](https://www.aliexpress.com/item/5V-Stepper-Motor-28BYJ-48-With-Drive-Test-Module-Board-ULN2003-5-Line-4-Phase/32608569300.html?spm=2114.13010608.0.0.HZtg9v)

### Setup

#### Wiring

- `5V <> 5V @ WEMOS D1`
- `5V <> + @ ULN2003`

- `GND <> G @ WEMOS D1`
- `GND <> - @ ULN2003`

- `D0 @ WEMOS D1 <> IN1 @ ULN2003`
- `D1 @ WEMOS D1 <> IN2 @ ULN2003`
- `D2 @ WEMOS D1 <> IN3 @ ULN2003`
- `D3 @ WEMOS D1 <> IN4 @ ULN2003`

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
