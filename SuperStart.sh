#!/bin/bash
# __  __  ______       ______  ______  __  __       ______  ______  __  __    
#/\ \_\ \/\  __ \     /\  == \/\  __ \/\ \_\ \     /\  == \/\  __ \/\_\_\_\   
#\ \____ \ \  __ \    \ \  __<\ \ \/\ \ \____ \    \ \  _-/\ \  __ \/_/\_\/_  
# \/\_____\ \_\ \_\    \ \_____\ \_____\/\_____\    \ \_\   \ \_\ \_\/\_\/\_\ 
#  \/_____/\/_/\/_/     \/_____/\/_____/\/_____/     \/_/    \/_/\/_/\/_/\/_/

echo -e "Super Start \n"

# read input/output selections

echo "( ServerOptions.inDevices.postln; 0.exit; )" | sclang | grep -A 1 "( ServerOptions.inDevices.postln; 0.exit; )"
echo -e "\n\n"
read -p "Input Device: " inputDevice
echo -e "\n"

echo "( ServerOptions.outDevices.postln; 0.exit; )" | sclang | grep -A 1 "( ServerOptions.outDevices.postln; 0.exit; )"
echo -e "\n\n"
read -p "Output Device: " outputDevice
echo -e "\n"

# if nonempty, replace device with input string in SuperStart.scd and ship to sclang
# blank entries run sclang with last device written to SuperStart.scd

if [ -n "$inputDevice" ]; then
	sed -i "s/Server\.default\.options\.inDevice_(\".*\");/Server.default.options.inDevice_(\"$inputDevice\");/" SuperStart.scd
fi

if [ -n "$outputDevice" ]; then
	sed -i "s/Server\.default\.options\.outDevice_(\".*\");/Server.default.options.outDevice_(\"$outputDevice\");/" SuperStart.scd
fi

sclang SuperStart.scd
