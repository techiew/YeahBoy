#pragma once

#include <chrono>
#include <thread>
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
	CPU cpu;
	VRAM vram;
	WRAM wram;
	OAM oam;
	HRAM hram;
	Bus bus;
	Cartridge cartridge;

public:
	YeahBoy();
	void Start();
	bool InsertCartridge(std::string filepath);
	~YeahBoy();
};