#pragma once

#include <vector>
#include "DebugConsole.h"

class WRAM
{
private: 
	std::vector<uint8_t> bytes = std::vector<uint8_t>(8000, 0);

public:
	uint8_t Read(uint16_t address);
	bool Write(uint16_t address, uint8_t byte);
};