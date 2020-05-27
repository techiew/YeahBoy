#pragma once

#include <cstdint>
#include <vector>
#include "DebugConsole.h"

class Cartridge
{
private:
	std::vector<uint8_t> rom = std::vector<uint8_t>(32000, 0);
	std::vector<uint8_t> eram = std::vector<uint8_t>(8000, 0);

public:
	bool LoadROM(std::string filepath);
	uint8_t ReadROM(uint16_t address);
	uint8_t Read(uint16_t address);
	bool Write(uint16_t address, uint8_t byte);
};