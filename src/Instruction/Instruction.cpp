#include <Instruction.hpp>


inline std::string getWord(const std::string& str, int& i) {
	std::string subStr;
	while (str[i] != ' ' && str[i] != ',' && i < str.length()) {
		subStr += str[i++];
	}
	++i;
	return subStr;
}

Argument parseArgument(std::string str) {
	Argument a;
	switch (str[0]) {
		case 'R':
			a.type = ARG_TYPE_REGISTER;
			a.value = str[1] - '0';
			break;
		case '[':
			a.type = ARG_TYPE_ADDRESS;
			break;
		case '#':
			a.type = ARG_TYPE_IMMEDIATE;
			a.value = str[1] - '0';
			break;
		default:
			std::cout << str << std::endl;
			throw std::invalid_argument("Unknown argument");
			break;
	}

	return a;
}

Instruction parseInstruction(std::string rawInstruction) {
	Instruction i = {};
	int p = 0;

	// Get Mnemonic
	std::string mnemonicStr = getWord(rawInstruction, p);
	i.mnemonic = MnemonicMap[mnemonicStr];

	// Get Arguments
	while (p < rawInstruction.length()) {
		i.arguments.push_back( parseArgument( getWord(rawInstruction, p) )  );
	}

	return i;
}
