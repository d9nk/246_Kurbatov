#!/bin/sh

sum() {
    expr $1 + $2
}

while read a b; do
    sum $a $b
done
