#!/bin/sh
# ewp.view.cgi
#	calls on dropdown.cgi to produce select options
#	for pagenames
#

cat ewp.view
./dropdown.cgi "pagename"
echo "<input type='submit' value=' view '>"
echo "</form></dd>"

