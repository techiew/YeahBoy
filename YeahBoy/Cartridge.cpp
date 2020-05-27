#include "Cartridge.h"

bool Cartridge::LoadROM(std::string filepath)
{
	return false;
}

uint8_t Cartridge::ReadROM(uint16_t address)
{
	int offset = address - 0x0000;

	if (offset < 0 || offset > (rom.size() - 1))
	{
		PrintDebugMsg("CARTRIDGE ROM ERROR: tried to read memory out of range", 0);
		return 0;
	}

	return rom.at(offset);
}

uint8_t Cartridge::Read(uint16_t address)
{
	int offset = address - 0xA000;

	if (offset < 0 || offset > (eram.size() - 1))
	{
		PrintDebugMsg("CARTRIDGE ERAM ERROR: tried to read memory out of range", 0);
		return 0;
	}

	return eram.at(offset);
}

bool Cartridge::Write(uint16_t address, uint8_t byte)
{
	int offset = address - 0xA000;

	if (offset < 0 || offset > (eram.size() - 1))
	{
		PrintDebugMsg("CARTRIDGE ERAM ERROR: tried to write to memory out of range", 0);
		return false;
	}

	eram.at(offset) = byte;

	return true;
}