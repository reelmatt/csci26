#!/bin/sh
#
# view_page.cgi
# cgi program to display current state of page
# simply takes the page name from form and passes it to mwp.cgi
# as QUERY_STRING and as $1
#

	eval `./qryparse`

	QUERY_STRING=$pagename
	export QUERY_STRING

	./mwp.cgi $pagename
