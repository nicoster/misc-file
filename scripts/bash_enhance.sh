#!/bin/bash

export GREP_OPTIONS="--exclude=\*.svn\*"
alias ll='ls -lh'
alias shp='vi ~/.bash_profile&&source ~/.bash_profile'
alias beep='echo -e "\a"'
PS1='\u:\w \$ '
alias sgrep='echo "Search source but ignore binary and .svn";grep -Ir --exclude "*\.svn*"'
alias rmbuild='find . -name "build"|xargs rm -r'
#alias goopy="ps -A|grep /Goopy|awk '{print \$1}'|xargs kill 2>nul"


#alias chrome='open -a /Applications/Google\ Chrome.app --args --enable-experimental-extension-apis'
alias chrome='open -a ~/chromium/src/xcodebuild/Debug/Chromium.app --args --enable-experimental-extension-apis'


