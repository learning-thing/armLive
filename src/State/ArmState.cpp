#include <ArmState.hpp>

u32 ArmCortexMCPU::programLength() {
	return program.size();;
}

bool ArmCortexMCPU::programEnd() {
	return (P_PC >= program.size());
}

void ArmCortexMCPU::executeNextInstruction(bool verbose) {
	if (P_PC < program.size())
		executeInstruction(program[P_PC], verbose);
}

void ArmCortexMCPU::executeInstruction(const Instruction& inst, bool verbose) {
	if (verbose) printInstruction(inst);
	if (P_PC == program.size()) {
		program.push_back(inst);
	}

	if (P_PC > program.size()-1) return;
	P_PC += 1;//Pseudo PC
	PC   += 4;

	switch (inst.mnemonic) {
		case MOV: {
			if (inst.arguments[0].type == ARG_TYPE_REGISTER && inst.arguments[1].type == ARG_TYPE_REGISTER) {
				R[inst.arguments[0].value] = R[inst.arguments[1].value];
			} else {
				throw std::invalid_argument("Unexpected argument types (expected: )");
			}
			break;
		}
		case LDR: {
			if (inst.arguments.size() == 2) {
				if (inst.arguments[0].type == ARG_TYPE_REGISTER && inst.arguments[1].type == ARG_TYPE_IMMEDIATE) {
					R[inst.arguments[0].value] = inst.arguments[1].value;
				}
			} else {
				std::invalid_argument("Error: Unexpected number of arguments (expected 2)");
			}
			break;
		}
		case ADD: {
			clearFlags();
			if (inst.arguments.size() == 2) {
				if (inst.arguments[0].type == ARG_TYPE_REGISTER && inst.arguments[1].type == ARG_TYPE_IMMEDIATE) {
					R[inst.arguments[0].value] += inst.arguments[1].value;
				} else {
					if (inst.arguments[0].type == ARG_TYPE_REGISTER && inst.arguments[1].type == ARG_TYPE_REGISTER) {
						R[inst.arguments[0].value] += R[inst.arguments[1].value];
					}
				}
			}
			break;
		}
		case SUB: {
			clearFlags();
			if (inst.arguments.size() == 2) {
				if (inst.arguments[0].type == ARG_TYPE_REGISTER && inst.arguments[1].type == ARG_TYPE_IMMEDIATE) {
					R[inst.arguments[0].value] -= inst.arguments[1].value;
				} else if (inst.arguments[0].type == ARG_TYPE_REGISTER && inst.arguments[1].type == ARG_TYPE_REGISTER) {
					R[inst.arguments[0].value] -= R[inst.arguments[1].value];
				}
				if (R[inst.arguments[0].value] == 0) {
					setFlag(FLAG_ZERO);
				}
			}
			break;
		}
		case BNE: {
			if (inst.arguments.size() == 1) {
				if (!getFlag(FLAG_ZERO)) {
					P_PC = inst.arguments[0].value;
					PC   = P_PC * 4;
				}
			} else {
				std::invalid_argument("Error: Unexpected number of arguments (expected 1)");
			}
			break;
		}
		case BEQ: {
			if (inst.arguments.size() == 1) {
				if (getFlag(FLAG_ZERO)) {
					P_PC = inst.arguments[1].value;
					PC   = P_PC * 4;
				}
			} else {
				std::invalid_argument("Error: Unexpected number of arguments (expected 1)");
			}
			break;
		}
		default:
			throw std::invalid_argument("Error: Unknown Instruction");
			break;
	}
}

void ArmCortexMCPU::dumpRegisters(std::string file) {
	std::ofstream registerDumpFile(file);
	for (int i = 0; i < 32; ++i) {
		registerDumpFile << R[i] << " ";
	}
	registerDumpFile << "\n";
}

bool ArmCortexMCPU::getFlag(Flag f) {
	return (Flags & f) > 0;
}

void ArmCortexMCPU::setFlag(Flag f) {
	Flags |= f;
}

void ArmCortexMCPU::clearFlags() {
	Flags = 0;
}
