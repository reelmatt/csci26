#!/bin/sh
# mwp.cgi
#	Generates html from fl datafiles
#	input: QUERY_STRING, as the page identifier (e.g. cities)
#	output: html sent directly to browser
#	method: calls on fl program to create table rows, uses header/footer
#	        files to complete HTML
#
	echo "Content-Type: text/html"
	echo ""

	# check to see if the user passed through a value
	if [ ! $QUERY_STRING ]
	then
		echo "Please enter in a pagename to look for"
	fi

	# check to see if a file actually exists
	# quoting QUERY_STRING prevents * bug
	if [ ! -f data/"$QUERY_STRING".tab ]
	then
		echo "Could not find page \"$QUERY_STRING.tab\""
	# print out customized header, followed by row data
	else
		./header.cgi "$QUERY_STRING"
		./fl row.fmt -d"|" data/"$QUERY_STRING".tab

		# check to see if ./fl output without errors
		if [ $? -ne 0 ]
		then
			echo "There was a problem parsing \"$QUERY_STRING.tab\". Try again."
			exit 1
		fi
		cat mwp.footer
	fi

	exit 0
