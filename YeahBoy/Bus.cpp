#include "Bus.h"

Bus::Bus()
{
}

Bus::Bus(VRAM* vram, WRAM* wram, OAM* oam, HRAM* hram, Cartridge* cartridge)
{
	this->vram = vram;
	this->wram = wram;
	this->oam = oam;
	this->hram = hram;
	this->cartridge = cartridge;
}

uint8_t Bus::Read(uint16_t address)
{

	if (address <= 0x7FFF) // ROM
	{
		return cartridge->ReadROM(address);
	}
	else if (address <= 0x9FFF) // Video memory (VRAM)
	{
		return vram->Read(address);
		//return memory.Read(memory.Sections.VRAM, address);
	}
	else if (address <= 0xBFFF) // External RAM (ERAM, inside cartridge)
	{
		return cartridge->ReadERAM(address);
	}
	else if (address <= 0xDFFF) // Work RAM (normal memory)
	{
		return wram->Read(address);
	}
	else if (address <= 0xFDFF) // An echo (clone/copy) of the work RAM, usually not used
	{
		return wram->Read(address);
	}
	else if (address <= 0xFE9F) // OAM (object attribute memory/sprite attribute table)
	{
		return oam->Read(address);
	}
	else if (address <= 0xFEFF) // Unusable memory
	{
		// Cannot read from this
	}
	else if (address <= 0xFF7F) // I/O ports (sound and video display)
	{
		// TO-DO
	}
	else if (address <= 0xFFFE) // High RAM (HRAM), RAM that is quick to access, used for specific tasks
	{
		return hram->Read(address);
	}
	else if (address <= 0xFFFF) // Interrupt enable register
	{
		return ir;
	}

	return 0x00;
}

bool Bus::Write(uint16_t address, uint8_t byte)
{

	if (address <= 0x7FFF) // ROM
	{
		// Cannot write to this
	}
	else if (address <= 0x9FFF) // Video memory (VRAM)
	{ 
		vram->Write(address, byte);
	}
	else if (address <= 0xBFFF) // External RAM (ERAM, inside cartridge)
	{
		cartridge->Write(address, byte);
	}
	else if (address <= 0xDFFF) // Work RAM (normal memory)
	{
		wram->Write(address, byte);
	}
	else if (address <= 0xFDFF) // An echo (clone/copy) of the work RAM, usually not used
	{
		wram->Write(address, byte);
	}
	else if (address <= 0xFE9F) // OAM (object attribute memory/sprite attribute table)
	{
		oam->Write(address, byte);
	}
	else if (address <= 0xFEFF) // Unusable memory
	{
		// Cannot write to this
	}
	else if (address <= 0xFF7F) // I/O ports (sound and video display)
	{
		// TO-DO
	}
	else if (address <= 0xFFFE) // High RAM (HRAM), RAM that is quick to access, used for specific tasks
	{
		hram->Write(address, byte);
	}
	else if (address <= 0xFFFF) // Interrupt enable register
	{
		ir = byte;
	}

	return true;
}
