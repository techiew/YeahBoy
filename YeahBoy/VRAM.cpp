#include "VRAM.h"

uint8_t VRAM::Read(uint16_t address)
{
	int offset = address - 0x8000;

	if (offset < 0 || offset > (bytes.size() - 1))
	{
		PrintDebugMsg("VRAM ERROR: tried to read memory out of range", 0);
		return 0;
	}

	return bytes.at(offset);
}

bool VRAM::Write(uint16_t address, uint8_t byte)
{
	int offset = address - 0x8000;

	if (offset < 0 || offset > (bytes.size() - 1))
	{
		PrintDebugMsg("VRAM ERROR: tried to write to memory out of range", 0);
		return false;
	}

	bytes.at(offset) = byte;

	return true;
}