#!/bin/sh

cmd="yes"

basedir=/system/bin/
#read -p "Please press a key to continue, or enter [no] to exit: " cmd

if [ $cmd = "no" ]
then
	exit
fi


echo -e "\033[?25l" > /dev/tty1
echo "Load Gix ..." > /dev/tty1

sh -c 'setterm -blank 0 -powersave off -powerdown 0 < /dev/console > /dev/console 2>&1' 

insmod "$basedir"/gix.ko || exit 1

#major=$(awk "\$2==\"gix\" {print \$1}" /proc/devices)

awk '/gix/ {print $1}' /proc/devices > /dev/shm/gdev
major=`cat /dev/shm/gdev`
rm -f /dev/shm/gdev

echo "gix device major is $major ..."
rm -f /dev/gi
mknod  /dev/gi c $major 0


#export PATH=$PATH:/sdcard/:/sdcard/bin

#echo "cmd = $cmd"
#gpm -k

#/bin/setgraphics 1
#rxvt &
"$basedir"/giwm&
#giwm  &
#/bin/setgraphics 0



