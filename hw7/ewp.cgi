#!/bin/sh
# ewp.cgi
#	Generates html from various template files and cgi scripts
#
        echo "Content-Type: text/html"
        echo ""

	cat ewp.header		# text
	cat ewp.add		# text
	./ewp.delete.cgi
	./ewp.view.cgi
	cat ewp.footer		# text
