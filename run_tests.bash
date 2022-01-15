# !/bin/bash

compile_and_run()
{
	# compiling
	obj="$1_obj"
	tests="$2"
	out="$1_out"
	if ! g++ -Wextra -Werror -Wall -std=c++98 -D NS="$1" "$tests" -o "$obj" > /dev/null 2>&1 ; then
		echo " =================== Compiling error ================="
		echo
		g++ -Wextra -Werror -Wall -std=c++98 -D NS="$1" "$tests" -o "$obj"
		echo
		echo " ====================================================="
		exit 1
	fi
	# running
	if ! ./"$obj" | grep -v "NAMESPACE" > "$out"  ; then
		echo " =================== Running error ================="
		echo
		./"$obj"
		echo
		echo " ====================================================="
		return 1
	fi

	return 0
}

tests="$1"

if [ $# -ne 2 ] && [ $# -ne 1 ]; then
	echo "Usage: [ ./run_tests.bash <tests_file.cpp> ]"
	echo "Option: [ -r ~~ To Remove the objects and output files ]"
	exit 1
fi

if [ $# -eq 2 ]; then
	tests="$2"
fi

if ! ls $tests > /dev/null 2>&1 ; then
	echo " $tests : file not found!"
	exit 2
fi


if ! compile_and_run std "$tests"; then
	exit 2
fi


if ! compile_and_run ft "$tests"; then
	exit 2
fi

differ="$(diff ft_out std_out)"


if [ "$differ" != "" ] ; then
	printf "\n           ====================== FAILURE :( ========================\n\n"
	diff ft_out std_out > differrence.txt
	echo "==================== Check differrence.txt to see diff output ===================="
	echo
	exit 3
else
	printf "\n ========== SUCCESS ;) ==========\n\n"
fi

if [ $# -eq 2 ] && [ "$1" = "-r" ]; then
	/bin/rm -rf ft_obj std_obj ft_out std_out > /dev/null 2>&1
fi

exit 0