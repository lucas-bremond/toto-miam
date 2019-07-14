######################################################################################################################################################

# @project        Toto|Miam
# @file           tools/development/docker/Dockerfile
# @author         Lucas Brémond <lucas.bremond@gmail.com>
# @license        MIT License

######################################################################################################################################################

FROM attachix/c9-esp8266-sdk:latest

LABEL maintainer="lucas.bremond@gmail.com"

# Install and setup ZSH

RUN apk update \
 && apk upgrade \
 && apk add --no-cache zsh \
 && rm -f /etc/apk/cache/*

RUN sed -i -e "s/bin\/ash/bin\/zsh/" /etc/passwd

ENV SHELL /bin/zsh

ENTRYPOINT /bin/zsh

RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true \
 && git clone https://github.com/bhilburn/powerlevel9k.git /root/.oh-my-zsh/custom/themes/powerlevel9k \
 && git clone https://github.com/zsh-users/zsh-autosuggestions /root/.oh-my-zsh/custom/plugins/zsh-autosuggestions \
 && git clone https://github.com/zsh-users/zsh-syntax-highlighting.git /root/.oh-my-zsh/custom/plugins/zsh-syntax-highlighting

COPY .zshrc /root/.zshrc

# Install and build Sming

ENV SMING_HOME /opt/Sming/Sming

RUN git clone https://github.com/SmingHub/Sming.git /opt/Sming \
 && cd /opt/Sming \
 && git checkout origin/master \
 && git submodule init \
 && git submodule update \
 && cd /opt/Sming/Sming \
 && make

RUN apk add screen nano

######################################################################################################################################################
