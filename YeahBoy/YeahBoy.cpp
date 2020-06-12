#include "YeahBoy.h"

using namespace std::chrono;

YeahBoy::YeahBoy()
{
	vram = VRAM();
	wram = WRAM();
	oam = OAM();
	hram = HRAM();
	cartridge = Cartridge();
	bus = Bus(&vram, &wram, &oam, &hram, &cartridge);
	cpu = CPU(&bus);
}

void YeahBoy::Start()
{
	int frameRate = 60;
	long long frameTime = 16.6666666667;
	int cyclesPerFrame = cpu.clockSpeed / frameRate;

	int frameCounter = 0;
	auto secondBegin = steady_clock::now();

	while (true)
	{
		auto begin = steady_clock::now();
		auto secondEnd = steady_clock::now();

		int emulatedCycles = 0;

		while (emulatedCycles < cyclesPerFrame)
		{
			cpu.Clock();
			emulatedCycles++;
		}

		auto end = steady_clock::now();
		long long elapsedTime = duration_cast<milliseconds>(end - begin).count();

		if (elapsedTime < frameTime)
		{
			std::this_thread::sleep_for(milliseconds(frameTime - elapsedTime));
		}

		long long elapsedSeconds = duration_cast<seconds>(secondEnd - secondBegin).count();

		if (elapsedSeconds >= 1)
		{
			//std::cout << std::dec << "FPS: " << frameCounter << std::endl;
			frameCounter = 0;
			secondBegin = steady_clock::now();
		}

		frameCounter++;
	}

}

bool YeahBoy::InsertCartridge(std::string filepath)
{
	cartridge.LoadROM("example");
	return false;
}

YeahBoy::~YeahBoy()
{
}
