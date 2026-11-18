#pragma once
#include <Argument.hpp>
#include <common.hpp>
#include <Mnemonics.hpp>

struct Instruction {
	Mnemonic mnemonic;
	std::vector<Argument> arguments;
};

Instruction parseInstruction(std::string rawInstruction);

const std::string MnemonicToString[] = { "MOV", "LDR", "SUB", "ADD", "ADDS", "BNE", "BEQ" };

inline void printInstruction(const Instruction& inst) {
	std::cout << MnemonicToString[inst.mnemonic] << " ";
	for (int i = 0; i < inst.arguments.size(); ++i) {
		std::string type;
		switch (inst.arguments[i].type) {
			case ARG_TYPE_REGISTER:
				type = "R";
				break;
			case ARG_TYPE_IMMEDIATE:
				type = "#";
				break;
			case ARG_TYPE_ADDRESS:
				type = "[";
				break;
		}
		std::cout << std::hex << type << inst.arguments[i].value << ", " << std::dec;
	}
	std::cout << std::endl;
}
