#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

class Cartridge
{
private:
	std::vector<uint8_t> rom = std::vector<uint8_t>(32768, 0);
	std::vector<uint8_t> eram = std::vector<uint8_t>(8192, 0);

public:
	bool LoadROM(std::string filepath);
	uint8_t ReadROM(uint16_t address);
	uint8_t ReadERAM(uint16_t address);
	bool Write(uint16_t address, uint8_t byte);
};