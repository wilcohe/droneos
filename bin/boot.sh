#!/bin/bash

internet=$(ping google.com -c 1 | grep "1 packets received")
if [[ ${#internet} -gt 8 ]]
then
	export INTERNET=TRUE
else 
	export INTERNET=FALSE
fi

board=$(arduino-cli board list | awk '/arduino/')
IFS=' ' read -r -a  array <<< $board

if [[ ${#array[@]} -eq 0 ]]
then
	echo "No Board Present"
	echo ""
else 
	ARDUINO_PORT=${array[0]}
	export ARDUINO_PORT=$ARDUINO_PORT
fi

