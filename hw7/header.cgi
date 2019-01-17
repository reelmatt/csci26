#!/bin/sh
# header.cgi
#	Generates header html for a mwp page
#	input: $pagename, parsed from QUERY_STRING in mwp.cgi
#	output: html sent directly to browser
#	method: Uses $pagename in title and other places on site
#

echo "<!doctype html><html>"
echo "<!-- a web page called pagename -->"
echo "<head><title>$1</title></head>"

echo "<body bgcolor='white'>"
echo "<b>A Web Page for $1</b>"
echo "<hr>"
echo "Customized Links for $1"
echo "<p>"
echo "<center>"
echo "<table border='1' cellpadding='5'>"

