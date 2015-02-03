echo arg1 is $1  
echo arg2 is $2 
echo arg3 is $3  
echo arg# is $#  


# Check arguments.
case "$#" in
1)	echo case_ arg1
2)	echo case_ arg1
3)	echo case_ arg1
*)	echo "Usage: adduser user group home-dir" >&2; exit 1
esac

exit 0
