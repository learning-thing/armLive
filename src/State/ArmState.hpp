#pragma once
#include <Instruction.hpp>
#include <common.hpp>

enum Flag {
	FLAG_ZERO     = (1 << 0),
	FLAG_CARRY    = (1 << 1),
	FLAG_OVERFLOW = (1 << 2),
	FLAG_NEGATIVE = (1 << 3)
};

class ArmCortexMCPU {
	u8 RAM[0xFFFF] = {0};
	u32 R[32];//Register
	u32 PC = 0x100;//Program Counter
	u32 P_PC = 0;
	u32 SP = 0xFFFE;//Stack pointer
	u8 Flags = 0;
	std::vector<Instruction> program;
	public:
		bool programEnd();
		void executeInstruction(const Instruction& inst, bool verbose=false);
		void executeNextInstruction(bool verbose=false);
		void dumpRegisters(std::string file);
		u32 programLength();
		bool getFlag(Flag f);
		void setFlag(Flag f);
		void clearFlags();
};
