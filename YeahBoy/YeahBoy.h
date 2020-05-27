#pragma once

#include "CPU.h"
#include "Bus.h"
#include "Cartridge.h"
#include "VRAM.h"
#include "WRAM.h"
#include "OAM.h"
#include "HRAM.h"

class YeahBoy
{
private:
	DebugConsole debugConsole;
	CPU cpu;
	VRAM vram;
	WRAM wram;
	OAM oam;
	HRAM hram;
	Bus bus;

public:
	YeahBoy();
	void Start();
	bool InsertCartridge(std::string filepath);
	~YeahBoy();
};