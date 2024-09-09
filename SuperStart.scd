Server.default.waitForBoot {
	Server.default.options.inDevice_("MME : Microsoft Sound Mapper - Input, MME");
	Server.default.options.outDevice_("");
    s.options.memSize = 14512 * 128;
    s.reboot;
    s.sync;
    SuperDirt.start;
};
