#!/bin/sh
#
# cgi program to test tt2ht2
#
    echo "Content-type: text/html"
    echo ""
    ( cat part4b.top ; cat who.output | head -3 ) | ./tt2ht3
#	./tt2ht3 < part4b.top
    echo "</table>"
    ( cat part5b.bottom ; cat sched | head -5) | ./tt2ht3
#	cat part5b.top
#	printf '\n\n\n\n'
#	cat part5b.top | ./tt2ht3
    echo "</div></table></body></html>"
