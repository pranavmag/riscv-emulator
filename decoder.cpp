#include "decoder.h"
#include <iostream>
#include <string>
#include <cstdint>

uint32_t convertBinary(const std::string& binaryString) {
	uint32_t value{};

	for (char c : binaryString) {
		if (c != '0' && c != '1') {
			std::cout << "Invalid binary input\n";
			return 0;
		}
		int bit = c - '0';
		value = (value << 1) | bit;
	}

	return value;
}

uint32_t getOpCode(uint32_t value) {
	uint32_t opcode = value & 0x7F;

	return opcode;
}

uint32_t getRd(uint32_t value) {
	uint32_t rd = (value >> 7) & 0x1F;

	return rd;
}

uint32_t getFunct3(uint32_t value) {
	uint32_t funct3 = (value >> 12) & 0x7;

	return funct3;
}

uint32_t getRs1(uint32_t value) {
	uint32_t rs1 = (value >> 15) & 0x1F;

	return rs1;
}

int32_t getImm(uint32_t value) {
	uint32_t imm = (value >> 20) & 0xFFF;

	if (imm & 0x800) {
		return imm | 0xFFFFF000;
	}

	return imm;
}

int32_t getStoreImm(uint32_t value) {
	uint32_t imm_11_5 = (value >> 25) & 0x7F;

	uint32_t imm_4_0 = (value >> 7) & 0x1F;

	uint32_t imm = (imm_11_5 << 5) | imm_4_0;

	if (imm & 0x800) {
		return imm | 0xFFFFF000;
	}

	return imm;
}

int32_t getBranchImm(uint32_t value) {
	uint32_t imm_12 = (value >> 31) & 0x1;

	uint32_t imm_10_5 = (value >> 25) & 0x3F;

	uint32_t imm_4_1 = (value >> 8) & 0xF;

	uint32_t imm_11 = (value >> 7) & 0x1;

	uint32_t imm = (imm_12 << 12) | (imm_10_5 << 5) | (imm_4_1 << 1) | (imm_11 << 11);

	if (imm & 0x1000) {
		return imm | 0xFFFFE000;
	}

	return imm;

}

int32_t getJalImm(uint32_t value) {
	uint32_t imm_20 = (value >> 31) & 0x1;

	uint32_t imm_10_1 = (value >> 21) & 0x3FF;

	uint32_t imm_11 = (value >> 20) & 0x1;

	uint32_t imm_19_12 = (value >> 12) & 0xFF;

	uint32_t imm = (imm_20 << 20) | (imm_19_12 << 12) | (imm_11 << 11) | (imm_10_1 << 1);

	if (imm & 0x100000) {
		return imm | 0xFFE00000;
	}

	return imm;
}

uint32_t getFunct7(uint32_t value) {
	uint32_t funct7 = (value >> 25) & 0x7F;

	return funct7;
}

uint32_t getShamt(uint32_t value) {
	uint32_t shamt = (value >> 20) & 0x1F;

	return shamt;
}

uint32_t getRs2(uint32_t value) {
	uint32_t rs2 = (value >> 20) & 0x1F;

	return rs2;
}

DecodedInstruction decodeInstruction(uint32_t value) {
	DecodedInstruction inst{};

	uint32_t opcode{ getOpCode(value) };
	uint32_t funct3{ getFunct3(value) };
	uint32_t funct7{ getFunct7(value) };

	if (opcode == 0x13 && funct3 == 0x0) {
		inst.name = "addi";
		inst.type = TYPE_I;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.imm = getImm(value);
	}
	else if (opcode == 0x13 && funct3 == 0x7) {
		inst.name = "andi";
		inst.type = TYPE_I;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.imm = getImm(value);
	}
	else if (opcode == 0x13 && funct3 == 0x6) {
		inst.name = "ori";
		inst.type = TYPE_I;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.imm = getImm(value);
	}
	else if (opcode == 0x13 && funct3 == 0x4) {
		inst.name = "xori";
		inst.type = TYPE_I;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.imm = getImm(value);
	}
	else if (opcode == 0x13 && funct3 == 0x2) {
		inst.name = "slti";
		inst.type = TYPE_I;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.imm = getImm(value);
	}
	else if (opcode == 0x13 && funct3 == 0x3) {
		inst.name = "sltiu";
		inst.type = TYPE_I;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.imm = getImm(value);
	}
	else if (opcode == 0x13 && funct3 == 0x1 && funct7 == 0x0) {
		inst.name = "slli";
		inst.type = TYPE_SHIFT;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.shamt = getShamt(value);
	}
	else if (opcode == 0x13 && funct3 == 0x5 && funct7 == 0x0) {
		inst.name = "srli";
		inst.type = TYPE_SHIFT;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.shamt = getShamt(value);
	}
	else if (opcode == 0x13 && funct3 == 0x5 && funct7 == 0x20) {
		inst.name = "srai";
		inst.type = TYPE_SHIFT;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.shamt = getShamt(value);
	}
	else if (opcode == 0x33 && funct3 == 0x0 && funct7 == 0x0) {
		inst.name = "add";
		inst.type = TYPE_R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
	}
	else if (opcode == 0x33 && funct3 == 0x0 && funct7 == 0x20) {
		inst.name = "sub";
		inst.type = TYPE_R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
	}
	else if (opcode == 0x33 && funct3 == 0x7 && funct7 == 0x0) {
		inst.name = "and";
		inst.type = TYPE_R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
	}
	else if (opcode == 0x33 && funct3 == 0x6 && funct7 == 0x0) {
		inst.name = "or";
		inst.type = TYPE_R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
	}
	else if (opcode == 0x33 && funct3 == 0x4 && funct7 == 0x0) {
		inst.name = "xor";
		inst.type = TYPE_R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
	}
	else if (opcode == 0x33 && funct3 == 0x1 && funct7 == 0x0) {
		inst.name = "sll";
		inst.type = TYPE_R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
	}
	else if (opcode == 0x33 && funct3 == 0x5 && funct7 == 0x0) {
		inst.name = "srl";
		inst.type = TYPE_R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
	}
	else if (opcode == 0x33 && funct3 == 0x5 && funct7 == 0x20) {
		inst.name = "sra";
		inst.type = TYPE_R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
	}
	else if (opcode == 0x33 && funct3 == 0x2 && funct7 == 0x0) {
		inst.name = "slt";
		inst.type = TYPE_R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
	}
	else if (opcode == 0x33 && funct3 == 0x3 && funct7 == 0x0) {
		inst.name = "sltu";
		inst.type = TYPE_R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
	}
	else if (opcode == 0x23 && funct3 == 0x0) {
		inst.name = "sb";
		inst.type = TYPE_S;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getStoreImm(value);
	}
	else if (opcode == 0x23 && funct3 == 0x1) {
		inst.name = "sh";
		inst.type = TYPE_S;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getStoreImm(value);
	}
	else if (opcode == 0x23 && funct3 == 0x2) {
		inst.name = "sw";
		inst.type = TYPE_S;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getStoreImm(value);
	}
	else if (opcode == 0x63 && funct3 == 0x0) {
		inst.name = "beq";
		inst.type = TYPE_B;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getBranchImm(value);
	}
	else if (opcode == 0x63 && funct3 == 0x1) {
		inst.name = "bne";
		inst.type = TYPE_B;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getBranchImm(value);
	}
	else if (opcode == 0x63 && funct3 == 0x4) {
		inst.name = "blt";
		inst.type = TYPE_B;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getBranchImm(value);
	}
	else if (opcode == 0x63 && funct3 == 0x6) {
		inst.name = "bltu";
		inst.type = TYPE_B;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getBranchImm(value);
	}
	else if (opcode == 0x63 && funct3 == 0x5) {
		inst.name = "bge";
		inst.type = TYPE_B;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getBranchImm(value);
	}
	else if (opcode == 0x63 && funct3 == 0x7) {
		inst.name = "bgeu";
		inst.type = TYPE_B;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getBranchImm(value);
	}
	else if (opcode == 0x6F) {
		inst.name = "jal";
		inst.type = TYPE_J;
		inst.rd = getRd(value);
		inst.imm = getJalImm(value);
	}


	return inst;
}