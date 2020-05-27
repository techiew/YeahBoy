#pragma once

#include <cstdint>
#include "Bus.h"

class CPU
{
private:
	double clockSpeed = 0;
	uint16_t absoluteAddr = 0;
	uint16_t relativeAddr = 0;
	uint8_t fetched = 0;
	uint8_t opcode = 0;
	uint8_t cycles = 0;
	uint8_t* r1 = nullptr;
	uint8_t* r2 = nullptr;
	uint8_t* r3 = nullptr;
	uint8_t* r4 = nullptr;
	Bus* bus;

	struct ClockSpeeds
	{
		const double GB = 4.194304;
		const double SGB = 4.295454;
		const double GBC = 4.194304;
		const double GBCDS = 8.388608;
	};

	struct Registers
	{
		/*
		* 8-bit registers
		* A = accumulator
		* B, C, D, E, H, L = general purpose registers
		*/
		uint8_t a = 0, f = 0;
		uint8_t b = 0, c = 0, d = 0, e = 0, h = 0, l = 0;

		/*
		* 16-bit registers
		* SP = stack pointer, PC = program counter
		*/
		uint16_t sp = 0, pc = 0;
	};

	struct Flags // A bit field
	{
		uint8_t : 4; // Not used
		uint8_t cy : 1; // Carry flag
		uint8_t h : 1; // Half carry flag
		uint8_t n : 1; // Add/sub-flag
		uint8_t zf : 1; // Zero flag
	};

	/* 
	* A lowercase o stands for offset, which means to add left side value to right side value to get proper memory location
	*/

	bool
		NOP(), LDBC_d16(), LDaBC_A(), INCBC(), INCB(), DECB(), LDB_d8(), RLCA(), LDaa16_SP(), ADDHL_BC(), LDA_aBC(), DECBC(), INCC(), DECC(), LDC_d8(), RRCA(),
		STOP0(), LDDE_d16(), LDaDE_A(), INCDE(), INCD(), DECD(), LDD_d8(), RLA(), JRr8(), ADDHL_DE(), LDA_aDE(), DECDE(), INCE(), DECE(), LDE_d8(), RRA(),
		JRNZ_r8(), LDHL_d16(), LDapHL_A(), INCHL(), INCH(), DECH(), LDH_d8(), DAA(), JRZ_r8(), ADDHL_HL(), LDA_apHL(), DECHL(), INCL(), DECL(), LDL_d8(), CPL(),
		JRNC_r8(), LDSP_d16(), LDamHL_A(), INCSP(), INCaHL(), DECaHL(), LDaHL_d8(), SCF(), JRC_r8(), ADDHL_SP(), LDA_amHL(), DECSP(), INCA(), DECA(), LDA_d8(), CCF(),
		LDB_B(), LDB_C(), LDB_D(), LDB_E(), LDB_H(), LDB_L(), LDB_aHL(), LDB_A(), LDC_B(), LDC_C(), LDC_D(), LDC_E(), LDC_H(), LDC_L(), LDC_aHL(), LDC_A(),
		LDD_B(), LDD_C(), LDD_D(), LDD_E(), LDD_H(), LDD_L(), LDD_aHL(), LDD_A(), LDE_B(), LDE_C(), LDE_D(), LDE_E(), LDE_H(), LDE_L(), LDE_aHL(), LDE_A(),
		LDH_B(), LDH_C(), LDH_D(), LDH_E(), LDH_H(), LDH_L(), LDH_aHL(), LDH_A(), LDL_B(), LDL_C(), LDL_D(), LDL_E(), LDL_H(), LDL_L(), LDL_aHL(), LDL_A(),
		LDaHL_B(), LDaHL_C(), LDaHL_D(), LDaHL_E(), LDaHL_H(), LDaHL_L(), HALT(), LDaHL_A(), LDA_B(), LDA_C(), LDA_D(), LDA_E(), LDA_H(), LDA_L(), LDA_aHL(), LDA_A(),
		ADDA_B(), ADDA_C(), ADDA_D(), ADDA_E(), ADDA_H(), ADDA_L(), ADDA_aHL(), ADDA_A(), ADCA_B(), ADCA_C(), ADCA_D(), ADCA_E(), ADCA_H(), ADCA_L(), ADCA_aHL(), ADCA_A(),
		SUBB(), SUBC(), SUBD(), SUBE(), SUBH(), SUBL(), SUBaHL(), SUBA(), SBCA_B(), SBCA_C(), SBCA_D(), SBCA_E(), SBCA_H(), SBCA_L(), SBCA_aHL(), SBCA_A(),
		ANDB(), ANDC(), ANDD(), ANDE(), ANDH(), ANDL(), ANDaHL(), ANDA(), XORB(), XORC(), XORD(), XORE(), XORH(), XORL(), XORaHL(), XORA(),
		ORB(), ORC(), ORD(), ORE(), ORH(), ORL(), ORaHL(), ORA(), CPB(), CPC(), CPD(), CPE(), CPH(), CPL(), CPaHL(), CPA(),
		RETNZ(), POPBC(), JPNZ_a16(), JPa16(), CALLNZ_a16(), PUSHBC(), ADDA_d8(), RST00H(), RETZ(), RET(), JPZ_a16(), PREFIXCB(), CALLZ_a16(), CALLa16(), ADCA_d8(), RST08H(),
		RETNC(), POPDE(), JPNC_a16(), /*BLANK*/ CALLNC_a16(), PUSHDE(), SUBd8(), RST10H(), RETC(), RETI(), JPC_a16(), /*BLANK*/ CALLC_a16(), /*BLANK*/ SBCA_d8(), RST18H(),
		LDHaa8_A(), POPHL(), LDaC_A(), /*BLANK*/ /*BLANK*/ PUSHHL(), ANDd8(), RST20H(), ADDSP_r8(), JPaHL(), LDaa16_A(), /*BLANK*/ /*BLANK*/ /*BLANK*/ XORd8(), RST28H(),
		LDHA_aa8(), POPAF(), LDA_aC(), DI(), /*BLANK*/ PUSHAF(), ORd8(), RST30H(), LDHL_SPor8(), LDSP_HL(), LDA_aa16(), EI(), /*BLANK*/ /*BLANK*/ CPd8(), RST38H(),

		// Instructions prefixed with 0xCB (PREFIXCB instruction):
		RLCB(), RLCC(), RLCD(), RLCE(), RLCH(), RLCL(), RLCaHL(), RLCA(), RRCB(), RRCC(), RRCD(), RRCE(), RRCH(), RRCL(), RRCaHL(), RRCA(),
		RLB(), RLC(), RLD(), RLE(), RLH(), RLL(), RLaHL(), RLA(), RRB(), RRC(), RRD(), RRE(), RRH(), RRL(), RRaHL(), RRA(),
		SLAB(), SLAC(), SLAD(), SLAE(), SLAH(), SLAL(), SLAaHL(), SLAA(), SRAB(), SRAC(), SRAD(), SRAE(), SRAH(), SRAL(), SRAaHL(), SRAA(),
		SWAPB(), SWAPC(), SWAPD(), SWAPE(), SWAPH(), SWAPL(), SWAPaHL(), SWAPA(), SRLB(), SRLC(), SRLD(), SRLE(), SRLH(), SRLL(), SRLaHL(), SRLA(),
		BIT0_B(), BIT0_C(), BIT0_D(), BIT0_E(), BIT0_H(), BIT0_L(), BIT0_aHL(), BIT0_A(), BIT1_B(), BIT1_C(), BIT1_D(), BIT1_E(), BIT1_H(), BIT1_L(), BIT1_aHL(), BIT1_A(),
		BIT2_B(), BIT2_C(), BIT2_D(), BIT2_E(), BIT2_H(), BIT2_L(), BIT2_aHL(), BIT2_A(), BIT3_B(), BIT3_C(), BIT3_D(), BIT3_E(), BIT3_H(), BIT3_L(), BIT3_aHL(), BIT3_A(),
		BIT4_B(), BIT4_C(), BIT4_D(), BIT4_E(), BIT4_H(), BIT4_L(), BIT4_aHL(), BIT4_A(), BIT5_B(), BIT5_C(), BIT5_D(), BIT5_E(), BIT5_H(), BIT5_L(), BIT5_aHL(), BIT5_A(),
		BIT6_B(), BIT6_C(), BIT6_D(), BIT6_E(), BIT6_H(), BIT6_L(), BIT6_aHL(), BIT6_A(), BIT7_B(), BIT7_C(), BIT7_D(), BIT7_E(), BIT7_H(), BIT7_L(), BIT7_aHL(), BIT7_A(),
		RES0_B(), RES0_C(), RES0_D(), RES0_E(), RES0_H(), RES0_L(), RES0_aHL(), RES0_A(), RES1_B(), RES1_C(), RES1_D(), RES1_E(), RES1_H(), RES1_L(), RES1_aHL(), RES1_A(),
		RES2_B(), RES2_C(), RES2_D(), RES2_E(), RES2_H(), RES2_L(), RES2_aHL(), RES2_A(), RES3_B(), RES3_C(), RES3_D(), RES3_E(), RES3_H(), RES3_L(), RES3_aHL(), RES3_A(),
		RES4_B(), RES4_C(), RES4_D(), RES4_E(), RES4_H(), RES4_L(), RES4_aHL(), RES4_A(), RES5_B(), RES5_C(), RES5_D(), RES5_E(), RES5_H(), RES5_L(), RES5_aHL(), RES5_A(),
		RES6_B(), RES6_C(), RES6_D(), RES6_E(), RES6_H(), RES6_L(), RES6_aHL(), RES6_A(), RES7_B(), RES7_C(), RES7_D(), RES7_E(), RES7_H(), RES7_L(), RES7_aHL(), RES7_A(),
		SET0_B(), SET0_C(), SET0_D(), SET0_E(), SET0_H(), SET0_L(), SET0_aHL(), SET0_A(), SET1_B(), SET1_C(), SET1_D(), SET1_E(), SET1_H(), SET1_L(), SET1_aHL(), SET1_A(),
		SET2_B(), SET2_C(), SET2_D(), SET2_E(), SET2_H(), SET2_L(), SET2_aHL(), SET2_A(), SET3_B(), SET3_C(), SET3_D(), SET3_E(), SET3_H(), SET3_L(), SET3_aHL(), SET3_A(),
		SET4_B(), SET4_C(), SET4_D(), SET4_E(), SET4_H(), SET4_L(), SET4_aHL(), SET4_A(), SET5_B(), SET5_C(), SET5_D(), SET5_E(), SET5_H(), SET5_L(), SET5_aHL(), SET5_A(),
		SET6_B(), SET6_C(), SET6_D(), SET6_E(), SET6_H(), SET6_L(), SET6_aHL(), SET6_A(), SET7_B(), SET7_C(), SET7_D(), SET7_E(), SET7_H(), SET7_L(), SET7_aHL(), SET7_A();

	// Generic functions that provide the implementations for instructions of the same type
	// Lowercase z here means offsetting by the zero page (0xFF00 + register), 0xFF is specified as the zero page on the GameBoy for some weird reason
	// Uppercase R means any of the register(s) to perform the operation on, provided by the caller
	// Instructions with no operand do not have and do not need a generic implementation
	bool
		// 8-bit loads
		ImpLDR_d8(), ImpLDRR_d8(), ImpLDR_R(), ImpLDR_aRR(), ImpLDaRR_R(), ImpLDR_aa16, ImpLDR_d16(),
		ImpLDR_azR(), ImpLDazR_R(), ImpLDazd8_R(), ImpLDR_azd8(),
		// 16-bit loads
		ImpLDRR_d16(), ImpLDRR_RR(), ImpLDRR_RRod8(), ImpLDaa16_RR(), ImpPUSHRR(), ImpPOPRR(),
		// 8-bit ALU
		ImpADDR_R(), ImpADDR_aRR(), ImpADDR_d8(), ImpADCR_R(), ImpADCR_aRR(), ImpADCR_d8(), ImpSUBR_R(),
		ImpSUBR_aRR(), ImpSUBR_d8(), ImpSBCR_R(), ImpSBCR_aRR(), ImpSBCR_d8(), ImpANDR_R(), ImpANDR_aRR(), 
		ImpANDR_d8(), ImpORR_R(), ImpORR_aRR(), ImpORR_d8(), ImpXORR_R(), ImpXORR_aRR(), ImpXORR_d8(),
		ImpCPR_R(), ImpCPR_aRR(), ImpCPR_d8(), ImpINCR(), ImpINCaRR(), ImpDECR(), ImpDECaRR(), 
		// 16-bit arithmetic
		ImpADDRR_RR(), ImpADDRR_r8(), ImpINCRR(), ImpDECRR(), 
		// Miscellaneous
		ImpSWAPR(), ImpSWAPaRR(), 
		// Rotates & shifts
		ImpRLCR(), ImpRLCaRR(), ImpRLR(), ImpRLaRR(), ImpRRCR(), ImpRRCaRR(), ImpRRR(), ImpRRaRR(),
		ImpSLAR(), ImpSLAaRR(), ImpSRAR(), ImpSRAaRR(), ImpSRLR(), ImpSRLaRR(), 
		// Bit opcodes
		ImpBITR(), ImpBITaRR(),

	struct Instruction
	{
		std::string mnemonic;
		uint8_t opcode;
		uint8_t size;
		uint8_t cycles[2];
		bool (CPU::*operation)(void) = nullptr;
		bool (CPU::*addressingMode)(void) = nullptr;
	};

	std::vector<Instruction> IS = {
		{"NOP", 0x00, 1, {4}, &NOP, &mode}
	};

	ClockSpeeds clockSpeeds;
	Registers registers;
	Flags flags;

	uint8_t Fetch();

public:
	CPU();
	CPU(Bus* bus);
	void Clock();
	void interruptRequest();
	void interruptRequestNonMaskable();
	~CPU();
};