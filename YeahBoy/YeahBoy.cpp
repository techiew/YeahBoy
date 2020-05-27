#include "YeahBoy.h"

YeahBoy::YeahBoy()
{
	debugConsole = DebugConsole();
	vram = VRAM();
	wram = WRAM();
	oam = OAM();
	hram = HRAM();
	bus = Bus(&vram, &wram, &oam, &hram);
	cpu = CPU(&bus);
}

void YeahBoy::Start()
{

	while (true)
	{
		cpu.Clock();
	}

}

bool YeahBoy::InsertCartridge(std::string filepath)
{
	return false;
}

YeahBoy::~YeahBoy()
{
}
