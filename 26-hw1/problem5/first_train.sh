#!/bin/sh
# first_train.sh
# usage: first_train station direction
# action: finds the first train for selected station and direction
#
        if test $# != 2
        then
            echo "usage: first_train station direction"
            exit 1
        fi

        printf '%s' "The first "
        if test $2 = i
        then
            printf '%s' "inbound"
        else
            printf '%s' "outbound"
        fi
        printf '%s \n' " train at $1 station is at:"
        grep "stn=$1" sched | grep "dir=$2" | cut -d ";" -f4 | sort | cut -d "=" -f2 | head -1