#!/bin/sh

if ls $* -I out > out 2> /dev/null; then
    echo YES
    cat out
else
    echo NO $?
fi
rm -f out
