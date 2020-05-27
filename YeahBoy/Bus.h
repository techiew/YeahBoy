#pragma once

#include "Cartridge.h"
#include "VRAM.h"
#include "WRAM.h"
#include "OAM.h"
#include "HRAM.h"

class Bus
{
private:
	Cartridge* cartridge;
	VRAM* vram;
	WRAM* wram;
	OAM* oam;
	HRAM* hram;
	uint8_t ir; // Interrupt enable register

public:
	Bus();
	Bus(VRAM* vram, WRAM* wram, OAM* oam, HRAM* hram);
	uint8_t Read(uint16_t address);
	bool Write(uint16_t address, uint8_t byte);
	~Bus();
};