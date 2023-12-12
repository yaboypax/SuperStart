Server.default.waitForBoot ({
	Server.default.options.inDevice = "Windows DirectSound : Primary Sound Capture Driver";
	Server.default.options.outDevice = "Windows DirectSound : Speakers (Synaptics SmartAudio HD)";
    s.options.memSize = 14512 * 128;
    s.reboot;
    s.sync;
    SuperDirt.start;
});
