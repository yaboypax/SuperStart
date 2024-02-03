# SuperStart:  Start Supercollider without Supercollider IDE

This is something I build pretty quickly so that I could just double click an application, select my audio input and output devices and run scsynth, sclang, and open the port to listen for signal from TidalCycles in VS Code. There's a lot to still do here, so please feel free to hit me with any suggestions or issues. This is my first forray into the Win32 desktop app API, so there's plenty I still am not aware of.

## Instructions

Unzip the most recent release into a SuperStart folder. Doubleclick the .exe and you'll be prompted to select an input and output device. Then hit launch and you should have the same consol output usually written into the Supercollider integrated console written to a cmd window. After that you'll have to close the window manually when you're done with a session or if you want to use the Kill button which sends a s.killAll message. 

You can adjust the SuperStart.scd startup file if you want, but make sure to preserve the lines designated for input and output device selection. It indexes this file by line number, so even adding an empty line at the top of the file will throw things off.
