#!/bin/sh
#
# delete_item.cgi
#
# this script is called from ewp.html for the Delete function
# If it finds a page with a corresponding title on it, it will
# delete the specified item from the page. It will send back a
# status report indicating if the item was there and if it was
# removed successfully (text copied from the assignment spec).
#

	eval `./qryparse`		# receive form data
	DATAFILE=$pagename.tab		# $pagename set by qryparse

	echo "Content-type: text/plain"	# tell browser type of output
	echo ""				# end of header

	if test ! -f data/$DATAFILE	# if no datafile
	then
		echo "There is no data file for $pagename"
		exit
	fi
	cd data

	# look to see if the title exists in the file
	if grep -q "title=$title" $DATAFILE
	then
		# if it exists, delete, store in a tmp "result" file
		sed /"title=$title"/d $DATAFILE > result

		# replace it in the original file, and print status msg
		mv result $DATAFILE
		echo "The item $title was found, and succesfully removed."
		echo "Press the Back button now."
	else
		echo "Did not find a record for $title in $DATAFILE"
	fi
