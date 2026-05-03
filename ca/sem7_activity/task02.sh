#!/bin/sh

A=`whoami`
Sys=`uname`
Msg="Hello, $A!
Welcome to $Sys!"

echo "$Msg"
