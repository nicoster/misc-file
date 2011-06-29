#!/bin/bash

export GREP_OPTIONS="--exclude=\*.svn\*"

alias wbt='adb pull /sdcard/imcius/wbxtrace/`adb shell ls -l /sdcard/imcius/wbxtrace/wbxConntra*|cut -c57-86|sort -r|head -n 1|tee /tmp/wbt` /tmp;cat /tmp/wbt'
alias ll='ls -lh'
alias ains='adb install -r'
#alias chrome='open -a /Applications/Google\ Chrome.app --args --enable-experimental-extension-apis'
alias chrome='open -a ~/chromium/src/xcodebuild/Debug/Chromium.app --args --enable-experimental-extension-apis'

alias a2l='$NDKROOT/toolchains/arm-linux-androideabi-4.4.3/prebuilt/darwin-x86/bin/arm-linux-androideabi-addr2line -e /workspace/collab/src/android/obj/local/armeabi/libimpjni.so'
alias lowres='newscreen -h 1280 -v 800'
alias rmbuild='find . -name "build"|xargs rm -r'
alias shp='vi ~/.bash_profile&&source ~/.bash_profile'
alias beep='echo -e "\a"'
alias ash='adb shell'
#alias aw='adb shell netcfg mlan0'
alias getso='echo cp x86 so to dc8/nick/libimpjni.so and cip_service folder;scp nick@10.224.168.103:/vob_nick/ip_phone/ip_g5/android/intel/2.2.0/mydroid/out/target/product/ivydale/obj/lib/libimpjni.so /Volumes/nick/libimpjni.so;cp /Volumes/nick/libimpjni.so /workspace/cip_impservice/libs/x86/libimpjni4.so'
alias cpso='cp /workspace/collab/src/android/libs/armeabi/libimpjni.so /workspace/cip_impservice/libs/armeabi/libimpjni.so'
#alias logcat='adb logcat |grep -v '\''ccservice\|DeviceStorageMonitorService'\''
alias pushso='scp jikky@10.224.168.103:/vob_nick/ip_phone/ip_g5/android/intel/2.2.0/mydroid/out/target/product/ivydale/obj/lib/libimpjni.so libimpjni.so&&adb push libimpjni.so /data/data/cip.impservice/lib'
alias logcat='adb logcat -c;adb logcat -v time|grep -i imp'
PS1='\u:\w \$ '
alias sgrep='echo "Search source but ignore binary and .svn";grep -Ir --exclude "*\.svn*"'

#alias goopy="ps -A|grep /Goopy|awk '{print \$1}'|xargs kill 2>nul"

