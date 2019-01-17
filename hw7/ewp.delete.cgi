#!/bin/sh
# ewp.delete.cgi
#	calls on dropdown.cgi to produce select options
#	for both pagenames and titles
#

cat ewp.delete
./dropdown.cgi "pagename"
./dropdown.cgi "title"
echo "<input type='submit' value=' delete '>"
echo "</form></dd>"

