#!/bin/sh
# cgi wrapper for ncal2
# Exercise 1a, adds ability to pass in a QUERY_STRING

	echo "Content-Type: text/plain"
	echo ""

	# check to see if the user passed through a value
	if [ ! "$QUERY_STRING" ]
	then
		echo "No month was requested. Here's the current month."
		./ncal2
	else
		MONTH=$(./name2num "$QUERY_STRING")

		# check to see if the QUERY is a valid month
		if [ $? -ne 0 ]
		then
			echo "\"$QUERY_STRING\" is not a valid month. Try again."
			exit 1
		fi

		# if a valid month, see if it is for a month that has passed
		if [ $MONTH -lt $(date +%m) ]
		then
			YEAR=$(expr $(date +%Y) + 1)
			./ncal2 $MONTH $YEAR		# print the next one if yes
		else
			./ncal2 $QUERY_STRING		# print the cur year if no
		fi
	fi

	exit 0
