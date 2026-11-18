#pragma once
#include <common.hpp>

enum ArgumentType {
	ARG_TYPE_REGISTER,
	ARG_TYPE_ADDRESS,
	ARG_TYPE_IMMEDIATE
};

enum ImmediateType {
	IMMEDIATE_HEX,
	IMMEDIATE_LABEL,
	IMMEDIATE_DEC
};

struct Argument {
	ArgumentType type;
	u32 value;
};
