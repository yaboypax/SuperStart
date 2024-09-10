#!/bin/bash

echo -e "Super Start \n"

echo "( ServerOptions.inDevices.postln; 0.exit; )" | sclang | grep -A 4 "( ServerOptions.inDevices.postln; 0.exit; )"
echo -e "\n\n"
read -p "Input Device: " inputDevice

echo "( ServerOptions.outDevices.postln; 0.exit; )" | sclang | grep -A 4 "( ServerOptions.outDevices.postln; 0.exit; )"
echo -e "\n\n"
read -p "Output Device: " outputDevice

sed -i "s/Server\.default\.options\.inDevice_(\".*\");/Server.default.options.inDevice_(\"$inputDevice\");/" SuperStart.scd
sed -i "s/Server\.default\.options\.outDevice_(\".*\");/Server.default.options.outDevice_(\"$outputDevice\");/" SuperStart.scd

sclang SuperStart.scd
