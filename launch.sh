#!/bin/bash

CONFIG='--config=./config/.irssi'

# check there is one argument
if [ $# -ne 1 ]; then
	irssi $CONFIG
	exit 1
fi

if [ $# -eq 1 ]; then
	irssi -n $1 $CONFIG
fi

