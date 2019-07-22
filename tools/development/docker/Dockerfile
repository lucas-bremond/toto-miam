######################################################################################################################################################

# @project        Toto|Miam
# @file           tools/development/docker/Dockerfile
# @author         Lucas Brémond <lucas.bremond@gmail.com>
# @license        MIT License

######################################################################################################################################################

FROM ubuntu:18.04

LABEL maintainer="lucas.bremond@gmail.com"

# Install utilities

RUN apt-get update \
 && apt-get install -y git wget nano screen \
 && rm -rf /var/lib/apt/lists/*

# Install and setup ZSH

RUN apt-get update \
 && apt-get install -y zsh \
 && rm -rf /var/lib/apt/lists/*

RUN sed -i -e "s/bin\/bash/bin\/zsh/" /etc/passwd

ENV SHELL /bin/zsh

ENTRYPOINT /bin/zsh

RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true \
 && git clone https://github.com/bhilburn/powerlevel9k.git /root/.oh-my-zsh/custom/themes/powerlevel9k \
 && git clone https://github.com/zsh-users/zsh-autosuggestions /root/.oh-my-zsh/custom/plugins/zsh-autosuggestions \
 && git clone https://github.com/zsh-users/zsh-syntax-highlighting.git /root/.oh-my-zsh/custom/plugins/zsh-syntax-highlighting

COPY .zshrc /root/.zshrc

# Install build tools

RUN apt-get update \
 && apt-get install -y make unrar autoconf automake libtool libtool-bin gcc g++ gperf flex bison texinfo gawk ncurses-dev libexpat1-dev python sed python-serial python-dev srecord bc git help2man unzip bzip2 \
 && rm -rf /var/lib/apt/lists/*

# Install esp-open-sdk

ENV CT_EXPERIMENTAL y
ENV CT_ALLOW_BUILD_AS_ROOT y
ENV CT_ALLOW_BUILD_AS_ROOT_SURE y

RUN git clone --recursive https://github.com/pfalcon/esp-open-sdk.git /opt/esp-open-sdk \
 && cd /opt/esp-open-sdk \
 && make VENDOR_SDK=1.5.4 STANDALONE=y

ENV ESP_HOME /opt/esp-open-sdk

# Get and Build Sming Core

RUN git clone https://github.com/SmingHub/Sming.git /opt/Sming
#  && cd /opt/Sming \
#  && git checkout tags/3.8.0

ENV SMING_HOME /opt/Sming/Sming

# Install esptool.py

RUN apt-get update \
 && apt-get install python-serial unzip \
 && rm -rf /var/lib/apt/lists/* \
 && wget https://github.com/themadinventor/esptool/archive/master.zip \
 && unzip master.zip \
 && mv esptool-master ${ESP_HOME}/esptool \
 && rm master.zip

# Install esptool2

RUN cd ${ESP_HOME} \
 && git clone https://github.com/raburton/esptool2 \
 && cd esptool2 \
 && make

ENV PATH ${PATH}:${ESP_HOME}/esptool2

######################################################################################################################################################
