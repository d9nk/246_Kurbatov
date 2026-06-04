#!/bin/sh

sum() {
    s=0
    for x; do
        s=`expr $s + $x 2>/dev/null`
        if [ $? -ne 0 ]; then
            echo 0
            return
        fi
    done
    echo $s
}

read line1
read line2

s1=`sum $line1`
s2=`sum $line2`

if [ "$s1" -eq "$s2" ]; then
    echo "Equal"
else
    echo "Not equal"
fi
