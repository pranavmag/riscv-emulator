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

std::string decodeInstruction(uint32_t opcode, uint32_t funct3, uint32_t funct7) {
	if (opcode == 0x13) {  // addi instruction
		if (funct3 == 0x0) {
			return "addi";
		}
		else if (funct3 == 0x7) {  // andi instruction
			return "andi";
		}
		else if (funct3 == 0x6) {  // ori instruction
			return "ori";
		}
		else if (funct3 == 0x4) {  // xori instruction
			return "xori";
		}
		else if (funct3 == 0x2) {  // slti instruction
			return "slti";
		}
		else if (funct3 == 0x3) {  // sltiu instruction
			return "sltiu";
		}
		else if (funct3 == 0x1 && funct7 == 0x0) {  // slli instruction
			return "slli";
		}
		else if (funct3 == 0x5) {
			if (funct7 == 0x0) {
				return "srli";
			}
			else if (funct7 == 0x20) {
				return "srai";
			}
		}
	}
	else if (opcode == 0x33) {
		if (funct3 == 0x0) {
			if (funct7 == 0x0) {
				return "add";
			}
			else if (funct7 == 0x20) {
				return "sub";
			}
		}
	}

	return "unknown";

}