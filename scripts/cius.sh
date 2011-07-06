#!/bin/bash

cius_build_machine='10.224.118.180'
sshport=22

alias ciuswifi='adb shell svc wifi'
alias wbt='adb pull /sdcard/imcius/wbxtrace/`adb shell ls -l /sdcard/imcius/wbxtrace/wbxConntra*|cut -c57-86|sort -r|head -n 1|tee /tmp/wbt` /tmp;cat /tmp/wbt'
alias a2l='$NDKROOT/toolchains/arm-linux-androideabi-4.4.3/prebuilt/darwin-x86/bin/arm-linux-androideabi-addr2line -e /workspace/collab/src/android/obj/local/armeabi/libimpjni.so'
alias ash='adb shell'
alias logcat='adb logcat -c;adb logcat -v time|grep -i imp'
alias ains='adb install -r'
#alias aw='adb shell netcfg mlan0'
#alias getso='echo cp x86 so to dc8/nick/libimpjni.so and cip_service folder;scp nick@10.224.168.103:/vob_nick/ip_phone/ip_g5/android/intel/2.2.0/mydroid/out/target/product/ivydale/obj/lib/libimpjni.so /Volumes/nick/libimpjni.so;cp /Volumes/nick/libimpjni.so /workspace/cip_impservice/libs/x86/libimpjni4.so'
#alias cpso='cp /workspace/collab/src/android/libs/armeabi/libimpjni.so /workspace/cip_impservice/libs/armeabi/libimpjni.so'
#alias logcat='adb logcat |grep -v '\''ccservice\|DeviceStorageMonitorService'\''
#alias pushso='scp jikky@10.224.168.103:/vob_nick/ip_phone/ip_g5/android/intel/2.2.0/mydroid/out/target/product/ivydale/obj/lib/libimpjni.so libimpjni.so&&adb push libimpjni.so /data/data/cip.impservice/lib'


function mc()
{
	start=$(timer);

	cdir=$PWD
	dst=/workspace/cip_impservice/libs/armeabi/libimpjni4.so
	cd /workspace/collab/src
#svn up ..
	$NDKROOT/ndk-build MYPLATFORM=8 NDK_DEBUG=1 NDK_PROJECT_PATH=./android/ APP_BUILD_SCRIPT=./Android_arm.mk APP_MODULES='apcom threadipc conhelp xmppcore xmppsdk XmppMgr LoginMgr PersonMgr WapiClient ConnectConfigInfo Buff apXml Expat conhttp commonsession-jni sslgwclient-jni utiltp-jni impjni' 

	if [ $? -eq 0 ]; then
		echo 
		echo Build succeed. 
		echo Try to cp libimpjni.so to /workspace/cip_impservice/libs/armeabi
		cp /workspace/collab/src/android/libs/armeabi/libimpjni.so $dst && ls -l $dst && echo Done && cd /workspace/cip_impservice/ && ant debug && adb install -r  bin/cip-impservice-debug.apk
	fi
		 
	cd $cdir
	printf 'Elapsed time: %s\n' $(timer $start)
	beep
}

function mx()
{
	start=$(timer);

	echo 'SSH to cius build machine. build. cp libimpjni to /tmp directory and dc8/nick directory'
	newdir='/tmp/so/'`date +%Y%m%d.%H.%M`
	dst='/workspace/cip_impservice/libs/x86'
	ssh nick@$cius_build_machine -p $sshport 'source .bash_profile&&./mc.sh'&&scp -P $sshport nick@$cius_build_machine:/vob_nick/ip_phone/ip_g5/android/intel/2.2.0/mydroid/out/target/product/ivydale/obj/lib/libimpjni.so $dst&& cp $dst/libimpjni.so $dst/libimpjni4.so 
	ls -l $dst

	dc8='/Volumes/nick/so/'`date +%Y%m%d.%H.%M`
	if [ $? -eq 0 ]; then
		echo Trying to cp libimpjni.so to $dc8 ..
		if mkdir $dc8 && cp $dst/libimpjni.so $dc8; then
			echo "Done"
		else
			echo "cp failed, you may cp it manually"
		fi
	fi
	beep
	printf 'Elapsed time: %s\n' $(timer $start)
	growlnotify -t 'SO build completed' -m 'Elapsed time: '$(timer $start) 2>/dev/null

}

function mxi()
{
	pushd 2> /dev/null
	cd /workspace/cip_impservice/ && ant debug && adb install -r bin/cip_impservice-debug-unaligned.apk  
#&& mv bin/cip_impservice-debug-unaligned.apk bin/cip_impservice.apk && ./sign.sh 
	popd 2> /dev/null
}

function f()
{
	echo $1
	echo $#
}

function aun()
{
	adb uninstall cip.impservice
	adb uninstall com.cisco.cius.im.client
}

function mo()
{
	umount /Volumes/ciusbuild
	mkdir /Volumes/ciusbuild 2> /dev/null
	sshfs -p $sshport nick@$cius_build_machine:/ /Volumes/ciusbuild
}
