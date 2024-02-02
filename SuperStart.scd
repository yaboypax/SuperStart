Server.default.waitForBoot ({
	Server.default.options.inDevice = "ASIO : Focusrite USB ASIO";
	Server.default.options.outDevice = "ASIO : Focusrite USB ASIO";
    s.options.memSize = 14512 * 128;
    s.reboot;
    s.sync;
    SuperDirt.start;
});
