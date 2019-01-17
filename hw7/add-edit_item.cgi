#!/bin/sh
#
# add-edit_item.cgi
# this script is called from ewp.html for the Add function
# it takes the specified items and creates a new record on the
# end of the named file in the data directory. For existing
# records, it updates any changed fields.
#

	eval `./qryparse`		# receive form data

	echo "Content-type: text/plain"	# tell browser type of output
	echo ""				# end of header


	# $1 is datafile, $2 is key, $3 is fieldname, $4 is fieldval
	# for a given record, identified by a key, it replaces the
	# existing value associated with "fieldname" with an updated
	# value
	replace_item ()
	{
		# if the user entered in a value, replace it
		if [ "$4" ]
		then
			# sed pattern modified from ex. written in Dec. 12 section
			sed "/^title=$2|/s+|$3=[^|]*+|$3=$4+;" $1 > $1.tmp

			# if successful, put modification in original file
			if [ $? = 0 ]
			then
				mv $1.tmp $1
			else
				echo "There was a problem replacing the field $3 with $2."
			fi
		fi
	}

	# $1 is title, $2 is titlecolor, $3 is descrip, $4 is url, $5 is datafile
	# when adding a new record to a data file, format and add to the
	# corresponding file
	add_to_file ()
	{
   		echo "adding to file..."
		printf "title=%s|tcolor=%s|desc=%s|url=%s\n" \
			"$1" "$2" "$3" "$4" >> $5

		if [ $? = 0 ]
		then
			echo "Addition of $1 was successful."
			echo "Please press the back button now."
		fi
	}

	if test ! -d data		# if no data directory
	then
		mkdir data		# try to make it
		if test $? -ne 0	# and check for errors
		then
			echo "Cannot create data directory."
			exit
		fi
	fi

	cd data

	if [ $pagename = "" -o $title = "" ]
	then
		echo "Both pagename and title are required."
		echo "Please press back, and try again."
	fi

	DATAFILE=$pagename.tab		# $pagename set by qryparse
	METHOD=""

	# if a file does not exist, no update to check
	# just add, and exit
	if test ! -f $DATAFILE
	then
		add_to_file "$title" "$titlecolor" "$descrip" "$url" "$DATAFILE"
		exit
	fi

	#check to see if a entry already exists for the given title
	grep -q "title=$title" "$DATAFILE"

	# if yes, replace only changed values
	if [ $? = 0 ]
	then
		replace_item "$DATAFILE" "$title" "tcolor" "$titlecolor"
		replace_item "$DATAFILE" "$title" "desc" "$descrip"
		replace_item "$DATAFILE" "$title" "url" "$url"
	# otherwise, add a new entry to the file
	else
		add_to_file "$title" "$titlecolor" "$descrip" "$url" "$DATAFILE"
		exit
	fi

	# adding already exits, so check to see if replace was successful
	if [ $? -eq 0 ]
	then
		echo "You successfully updated the $title record."
		echo "Press the Back button now."
	else
		echo "Unable to update file $DATAFILE ."
		echo "Please report to page admin."
	fi
