#pragma once

#include <string>
#include <cstdint>

inline const std::string TYPE_I = "I";
inline const std::string TYPE_R = "R";
inline const std::string TYPE_S = "S";
inline const std::string TYPE_SHIFT = "SHIFT";
inline const std::string TYPE_B = "B";
inline const std::string TYPE_J = "J";

struct DecodedInstruction {
	std::string name; // exact instruction: addi, slli, srai

	uint32_t rd{};
	uint32_t rs1{};
	uint32_t rs2{};

	int32_t imm{};
	uint32_t shamt{};

	std::string type;
};

DecodedInstruction decodeInstruction(uint32_t);

uint32_t convertBinary(const std::string&);

uint32_t getOpCode(uint32_t);

uint32_t getRd(uint32_t);

uint32_t getFunct3(uint32_t);

uint32_t getRs1(uint32_t);

int32_t getImm(uint32_t);

int32_t getStoreImm(uint32_t);

int32_t getBranchImm(uint32_t);

int32_t getJalImm(uint32_t);

uint32_t getFunct7(uint32_t);

uint32_t getShamt(uint32_t);

uint32_t getRs2(uint32_t);
