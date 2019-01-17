#!/bin/sh
# dropdown.cgi
#

	# check for number of args
	if [ $# -ne 1 ]
	then
		echo "usage: dropdown select-name-value"
	fi

	# check to see if there are pages available to view
	if [ "$(ls data/)" = "" ]
	then
		exit 1
	fi

	echo "<select name=\"$1\">"

	for f in data/*
	do
		printf "\t"

		if [ "$1" = "pagename" ]
		then
			./get_option -p $f
		elif [ "$1" = "title" ]
		then
			./get_option -t $f
		else
			echo "usage: pass in \"pagename\" or \"title\" to dropdown"
		fi
	done

	if [ $? = 0 ]
	then
		echo "</select>"
	fi

	exit 0
