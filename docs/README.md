## Misc. (to be removed)

### Mac OS X (native)

MacOS Sierra

Compiled ESP Alt SDK manually (fails on Sierra otherwise):
http://www.esp8266.com/wiki/doku.php?id=setup-osx-compiler-esp8266

To make it work:
Anaconda w/ Python 3 will conflict. I've removed it.

https://github.com/SmingHub/Sming/wiki/MacOS-Quickstart

git clone https://github.com/raburton/esptool2.git
cd esptool2 && make
export PATH=$PATH:PATH_TO_DIR/esptool2
export PATH=$PATH:/Users/lucas/Documents/Projets/TotoMiam/Software/esptool2

### Mac OS X (Docker)

* Not compatible with Docker 1.12 *

Install Docker for Mac OS X.

https://hub.docker.com/r/kireevco/sming-docker/

docker run -it -d -p 8181:80 -p 8122:22 -p 4075:4075 --device=/dev/cu.SLAB_USBtoUART -v ~/docker/sming-docker/workspace/:/root/workspace/ kireevco/sming-docker
docker run -it -d -p 8181:80 -p 8122:22 -p 4075:4075 --device=/dev/tty.SLAB_USBtoUART -v /Users/lucas/Documents/Projets/TotoMiam/Software/Test/:/root/workspace/ kireevco/sming-docker
docker run -it --privileged -d -p 8181:80 -p 8122:22 -p 4075:4075 --device=/dev/tty.SLAB_USBtoUART:/dev/ttyUSB0 -v /Users/lucas/Documents/Projets/TotoMiam/Software/Test/:/root/workspace/ kireevco/sming-docker
docker run -it -d -p 8181:80 -p 8122:22 -p 4075:4075 --device=/dev/tty.SLAB_USBtoUART:/dev/ttyUSB0 -v /Users/lucas/Documents/Projets/TotoMiam/Software/Test/:/root/workspace/ kireevco/sming-docker
docker run -it -d -p 8181:80 -p 8122:22 -p 4075:4075 --device /dev/tty.SLAB_USBtoUART -v /Users/lucas/Documents/Projets/TotoMiam/Software/Test/:/root/workspace/ kireevco/sming-docker

docker run --device /dev/tty.SLAB_USBtoUART kireevco/sming-docker

docker run -it --device /dev/tty.SLAB_USBtoUART test /bin/bash
docker run -it --privileged -v /dev/tty.SLAB_USBtoUART:/dev/tty.SLAB_USBtoUART test /bin/bash

make
make flash

screen /dev/cu.SLAB_USBtoUART 115200
screen /dev/tty.SLAB_USBtoUART 115200

## Hardware

### Motor Shield

https://smartarduino.gitbooks.io/user-mannual-for-esp-12e-motor-shield/content/index.html

alias python=python2.7?