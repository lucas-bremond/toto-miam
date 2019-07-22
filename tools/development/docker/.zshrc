export ZSH=/root/.oh-my-zsh

ZSH_THEME="robbyrussell"

ENABLE_CORRECTION="true"

plugins=(
  git
  zsh-autosuggestions
  zsh-syntax-highlighting
  python
  pip
  django
  celery
)

source $ZSH/oh-my-zsh.sh
