#include <iostream>
#include <ArmState.hpp>
#include <Instruction.hpp>


int main(int argc, char **argv) {
	ArmCortexMCPU cpu;

	std::cout << argc << std::endl;
	if (argc > 1) {
		std::ifstream script(argv[1]);
		std::string line;
		while (std::getline(script, line)) {
			Instruction inst = parseInstruction(line);
			cpu.executeInstruction(inst, true);
			while (!cpu.programEnd()) {
				cpu.executeNextInstruction(true);
			}
		}
		cpu.dumpRegisters("registers.txt");
		return 0;
	}

	while (true) {
		std::cout << "> ";
		std::string c;
		getline(std::cin, c);

		if (c.length() < 3) {
			cpu.dumpRegisters("registers.txt");
			continue;
		}
		if (c.empty()) continue;

		Instruction inst = parseInstruction(c);
		cpu.executeInstruction(inst);
	}



    return 0;
}
