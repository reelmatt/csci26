#!/bin/sh
# a hit counter

echo "Content-Type: text/html"
echo ""

echo "<html><body style='background-color:blue; color:white'>"
echo "<p>You are visitor number <span style='color:red'>"
./add1 < hits > hits.tmp
mv hits.tmp hits
cat hits
echo "</span></p></body></html>"
