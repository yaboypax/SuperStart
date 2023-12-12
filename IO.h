#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

std::vector<std::string> inputOptions{
    "MME : Microsoft Sound Mapper - Input",
    "MME : CABLE Output (VB-Audio Virtual",
    "MME : Microphone Array (Synaptics Sma",
    "Windows DirectSound : Primary Sound Capture Driver",
    "Windows DirectSound : CABLE Output (VB-Audio Virtual Cable)",
    "Windows DirectSound : Microphone Array (Synaptics SmartAudio HD)",
    "ASIO : ASIO4ALL v2",
    "ASIO : FL Studio ASIO",
    "ASIO : Generic Low Latency ASIO Driver",
    "ASIO : Focusrite USB ASIO"
};

std::vector<std::string> outputOptions{
    "MME : Microsoft Sound Mapper - Output",
    "MME : CABLE Output (VB-Audio Virtual",
    "MME : Microphone Array (Synaptics Sma",
    "MME : Speakers (Synaptics SmartAudio",
    "MME : CABLE Input (VB-Audio Virtual C",
    "MME : 2 - SHARP HDMI (AMD High Defini",
    "Windows DirectSound : Primary Sound Driver",
    "Windows DirectSound : Speakers (Synaptics SmartAudio HD)",
    "Windows DirectSound : CABLE Input (VB-Audio Virtual Cable",
    "Windows DirectSound : 2 - SHARP HDMI (AMD High Definition Audio Device)",
    "ASIO : ASIO4ALL v2",
    "ASIO : FL Studio ASIO",
    "ASIO : Generic Low Latency ASIO Driver",
    "ASIO : Focusrite USB ASIO"
};

class IOManager
{
public:

    void read()
    {
        std::ifstream read_file;
        read_file.open(filename);
        if (read_file.fail())
        {
            throw std::runtime_error("Unable to open file '" + filename + "' for reading.");
        }

        while (getline(read_file, line))
            lines.push_back(line);

        read_file.close();
    }

    void addInput(const std::string& string)
    {
        audioInput = string;
        audioInput.erase(std::remove(audioInput.begin(), audioInput.end(), '\0'), audioInput.end());
    }

    void addOutput(const std::string& string)
    {
        audioOutput = string;
        audioOutput.erase(std::remove(audioOutput.begin(), audioOutput.end(), '\0'), audioOutput.end());
    }

    void write()
    {
        std::ofstream write_file;
        write_file.open(filename);

        if (write_file.fail())
        {
            throw std::runtime_error("Unable to open file '" + filename + "' for writing.");
        }

        for (int i = 0; i < lines.size(); i++)
        {
            if (i != inputLine && i != outputLine)
            {
                write_file << lines[i] << std::endl;
            }
            else if (i == inputLine)
            {
                auto newString = "\tServer.default.options.inDevice = \"" + audioInput + "\";";
                write_file << newString << std::endl;
            }
            else if (i == outputLine)
            {
                auto newString = "\tServer.default.options.outDevice = \"" + audioOutput + "\";";
                write_file << newString << std::endl;
            }
        }

        write_file.close();
    }

private:
    std::string filename = "SuperStart.scd";
    std::string audioInput;
    std::string audioOutput;

    int inputLine = 1;
    int outputLine = 2;

    
    std::vector<std::string> lines;
    std::string line;

};
