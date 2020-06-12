#include "CPU.h"

using namespace std::chrono;

CPU::CPU()
{
}

CPU::CPU(Bus* bus)
{
	this->bus = bus;
	registers.SP = 0xFFFE;
	registers.PC = 0x0100;
	memset(&flags, 0, sizeof Flags);
	clockSpeed = clockSpeeds.GB;
	this->debugMode = true;
	this->debugBreak = true;

	if (debugMode)
	{
		registers.PC = 0x0000;
		PrintRegisters();
	}

	debugMemory = 
	{
		0x00, 0x01, 0xAB, 0xCD
	};
}

void CPU::Clock()
{

	if (cycles == 0)
	{

		if (debugMode)
		{
			if (registers.PC > (debugMemory.size() - 1)) return;
			std::cout << "Next instruction: " << IS[debugMemory[registers.PC]].mnemonic.c_str() << std::endl;
		}

		opcode = Fetch(registers.PC);

		if (IS[opcode].addressingMode != nullptr)
		{
			operand = (this->*(IS[opcode].addressingMode))();
		}

		if ((this->*(IS[opcode].operation))())
		{
			cycles = IS[opcode].cycles[0];
		}
		else
		{
			cycles = IS[opcode].cycles[1];
		}

		if (!jumped) registers.PC += IS[opcode].size;
		jumped = false;

		if (debugMode) PrintRegisters();
	}
	else
	{
		cycles--;
	}

}

uint8_t CPU::Fetch(uint16_t address)
{

	if (debugMode)
	{
		return debugMemory[address];
	}
	else
	{
		return bus->Read(address);
	}

}

void CPU::PrintRegisters()
{
	std::cout << "Register State:" << std::endl;
	std::cout << "A = 0x" << std::hex << std::uppercase << +registers.A;
	std::cout << " | F = C:" << +flags.C << " H:" << +flags.H << " N:" << +flags.N << " Z:" << +flags.Z << std::endl;
	std::cout << "B = 0x" << std::hex << std::uppercase << +registers.B << " | C = 0x" << std::hex << std::uppercase << +registers.C;
	std::cout << " | D = 0x" << std::hex << std::uppercase << +registers.D << " | E = 0x" << std::hex << std::uppercase << +registers.E;
	std::cout << " | H = 0x" << std::hex << std::uppercase << +registers.H << " | L = 0x" << std::hex << std::uppercase << +registers.L << std::endl;
	std::cout << "SP = 0x" << std::hex << std::uppercase << +registers.SP << " | PC = 0x" << std::hex << std::uppercase << +registers.PC << std::endl;
}

// Interrupts ----------------------------------------------
void CPU::InterruptRequest()
{
}

void CPU::InterruptRequestNonMaskable()
{
}

// Addressing modes ----------------------------------------
uint16_t CPU::Immediate()
{
	uint8_t highByte = Fetch(registers.PC + 1);
	uint8_t lowByte = Fetch(registers.PC + 2);
	return (highByte << 8) | lowByte;
}

// Instructions --------------------------------------------
bool CPU::NOP()
{
	return true;
}

bool CPU::LDBC_d16()
{
	r1 = &registers.B;
	r2 = &registers.C;
	return ImpLDRR_d16();
}

// Generic implementation functions ------------------------
bool CPU::ImpLDRR_d16()
{
	uint8_t high = operand >> 8;
	uint8_t low = operand;
	*r1 = high;
	*r2 = low;
	return true;
}