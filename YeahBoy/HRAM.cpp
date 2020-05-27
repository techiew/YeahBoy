#include "HRAM.h"

uint8_t HRAM::Read(uint16_t address)
{
	int offset = address - 0xFF80;

	if (offset < 0 || offset > (bytes.size() - 1))
	{
		PrintDebugMsg("HRAM ERROR: tried to read memory out of range", 0);
		return 0;
	}

	return bytes.at(offset);
}

bool HRAM::Write(uint16_t address, uint8_t byte)
{
	int offset = address - 0xFF80;

	if (offset < 0 || offset > (bytes.size() - 1))
	{
		PrintDebugMsg("HRAM ERROR: tried to write to memory out of range", 0);
		return false;
	}

	bytes.at(offset) = byte;
	
	return true;
}
