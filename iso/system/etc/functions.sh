
export ENV=/system/etc/ash.rc
#export GOOD="\e[32;40m\"
GOOD="\e[32;40m\ "
NORMAL="\e[0m "



get_bootparam() {
    local x copt params retval=1


    if [ ! -f /proc/kernel_param ] 
    then 
	echo "nofiles"
	 return 1
    fi

    params=`cat /proc/kernel_param`;


    for x in ${params} ; do
	#echo "find $x"
	if [ "$x" = "$1" ] ; then
                    echo "YES"

	    retval=0
	fi
    done

    return ${retval}
}


