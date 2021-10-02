#!/bin/bash

# if connected
if [[ printenv INTERNET ]] 
then 
	arduino-cli compile -b "$board" --output-dir ~/motor-code/ ~/motor-code/motor-code.ino

	arduino-cli upload -b "$board" -p "$port" ~/motor-code
else


if [[ -d "~/motor-code/" ]]
then
	mv ~/motor-code/ ~/old-motor-code/
fi

mkdir ~/motor-code
cd ~/motor-code

curl  https://raw.githubusercontent.com/wilcohe/droneos/main/motor-code/motor-code.ino > motor-code.ino

cd ~

if [[ -s "~/motor-code/motor-code.ino" ]] && [[ -d "~/old-motor-code" ]]
then
	rmdir -f ~/old-motor-code/
else
	mv ~/old-motor-code/ ~/motor-code
fi

board=$(~/bin/arduino-cli board list | awk '/arduino/')
IFS=' ' read -r -a array <<< $board

if [ ${#array[@]} -eq 0 ]; then 
	echo "No boards attached. Exiting. "
else
	board=${array[7]}
	core=${array[8]}
	port=${array[0]}
fi

install=$(arduino-cli core list | awk '/arduino:avr/')

if [[ -z "$install" ]] 
then
	arduino core install arduino:avr
fi

libs=$(cat ~/motor-code/motor-code.ino | awk '/include/' | sed 's|<*.h>||g' | sed 's|#include <||g' | tr -s '\n' ' ')
IFS=' ' read -r -a libraries <<< ${libs}

echo ""
echo ${libraries[2]}
echo ""

for library in "${libraries[@]}"
do 
	arduino-cli lib install $library
done

arduino-cli compile -b "$board" --output-dir ~/motor-code/ ~/motor-code/motor-code.ino

arduino-cli upload -b "$board" -p "$port" ~/motor-code

fi
