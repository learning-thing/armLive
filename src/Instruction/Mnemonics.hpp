#pragma once
#include <common.hpp>

enum Mnemonic {
	MOV,
	LDR,
	SUB,
	ADD,
	ADDS,
	BNE,
	BEQ
};

inline std::unordered_map<std::string, Mnemonic> MnemonicMap {
	{ "MOV",  MOV  },
	{ "LDR",  LDR  },
	{ "ADD",  ADD  },
	{ "ADDS", ADDS },
	{ "SUB",  SUB  },
	{ "BNE",  BNE  },
	{ "BEQ",  BEQ  }
};
