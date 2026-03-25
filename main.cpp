#include "decoder.h"
#include <iostream>
#include <string>
#include <cstdint>

std::string getBinary() {
	std::cout << "Enter a 32 bit binary string: ";
	std::string binaryString{};
	std::getline(std::cin >> std::ws, binaryString);

	return binaryString;
}

int main() {

	std::string binaryString{ getBinary() };
	uint32_t value{ convertBinary(binaryString) };

	uint32_t opcode{ getOpCode(value) };
	uint32_t rd{ getRd(value) };
	uint32_t funct3{ getFunct3(value) };
	uint32_t rs1{ getRs1(value) };
	uint32_t funct7{ getFunct7(value) };

	std::string instructionType{ decodeInstruction(opcode, funct3, funct7) };
	std::cout << instructionType << " x" << rd << ", x" << rs1 << ", ";

	if (instructionType == "slli" || instructionType == "srli" || instructionType == "srai") {
		uint32_t shamt{ getShamt(value) };
		std::cout << shamt << '\n';
		std::cout << "shamt: " << shamt << '\n';
		std::cout << "funct7: " << funct7 << '\n';
	}
	else {
		int32_t imm{ getImm(value) };
		std::cout << imm << '\n';
		std::cout << "immediate: " << imm << '\n';
	}

	std::cout << "Opcode: " << opcode << '\n';
	std::cout << "rd: " << rd << '\n';
	std::cout << "Funct3: " << funct3 << '\n';
	std::cout << "rs1: " << rs1 << '\n';

	std::cout << std::hex << "Raw Instruction (Hex): " << value << '\n';


	return 0;
}
