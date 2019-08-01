proc_pid=`pgrep -f a.out`
if [ ! "${proc_pid}x" = "x" ]; then
	echo the target pid is ${proc_pid}
	sudo kill -9 ${proc_pid}
else
	echo not exists
fi
