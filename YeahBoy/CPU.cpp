#include "CPU.h"

CPU::CPU()
{
}

CPU::CPU(Bus* bus)
{
	this->bus = bus;
	registers.sp = 0xFFFE;
	clockSpeed = clockSpeeds.GB;
}

void CPU::Clock()
{

	if (cycles == 0)
	{
		fetched = Fetch();
		registers.pc++;
	}

}

uint8_t CPU::Fetch()
{
	return bus->Read(registers.pc);
}

void CPU::interruptRequest()
{
}

void CPU::interruptRequestNonMaskable()
{
}

CPU::~CPU()
{
}
