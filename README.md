# SuperStart
## Initialize SuperCollider and SuperDirt for use with TidalCycles from Bash

This started as a command line application in C, then a C++ GUI app, but I realized I was an idiot and this is prime Bash Script territory. 

## Instructions

1. Download or clone SuperStart.sh and SuperStart.scd from this repo. Make sure both files are in the same directory.
2. Run the script and type in your input and output device selection.
    - Device options are printed for you before each read input so that you can copy/paste to make it even easier.
    - Blank entries initialize SuperCollider with the last selected audio devices
3. When script is finished running, you should see SuperDirt: listening to Tidal on port 57120.
4. Send commands from TidalCycles in your environment of choice. 
