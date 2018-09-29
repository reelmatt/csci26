#!/bin/sh
# first_train.cgi
# connector between first_train.html and first_train.sh
#
        eval $(./qryparse)
        echo "Content-type: text/plain"
        echo ""
        ./first_train.sh $station $direction