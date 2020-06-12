#include "OAM.h"

uint8_t OAM::Read(uint16_t address)
{
	int offset = address - 0xFE00;

	if (offset < 0 || offset > (bytes.size() - 1))
	{
		std::cerr << "OAM ERROR: tried to read memory out of range" << std::endl;
		return 0;
	}

	return bytes.at(offset);
}

bool OAM::Write(uint16_t address, uint8_t byte)
{
	int offset = address - 0xFE00;

	if (offset < 0 || offset > (bytes.size() - 1))
	{
		std::cerr << "OAM ERROR: tried to write to memory out of range" << std::endl;
		return false;
	}

	bytes.at(offset) = byte;

	return true;
}