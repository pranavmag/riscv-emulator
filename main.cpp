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
	while (true) {

		std::string binaryString{ getBinary() };

		if (binaryString == "quit") break;

		uint32_t value{ convertBinary(binaryString) };

		DecodedInstruction inst = decodeInstruction(value);

		if (inst.type == TYPE_I) {
			std::cout << inst.name << " x" << inst.rd << ", x" << inst.rs1 << ", " << inst.imm << '\n';
		}
		else if (inst.type == TYPE_SHIFT) {
			std::cout << inst.name << " x" << inst.rd << ", x" << inst.rs1 << ", " << inst.shamt << '\n';
		}
		else if (inst.type == TYPE_R) {
			std::cout << inst.name << " x" << inst.rd << ", x" << inst.rs1 << ", " << inst.rs2 << '\n';
		}
		else if (inst.type == TYPE_S) {
			std::cout << inst.name << " x" << inst.rs2 << ", " << inst.imm << "(x" << inst.rs1 << ")" << '\n';
		}
		else if (inst.type == TYPE_B) {
			std::cout << inst.name << " x" << inst.rs1 << ", x" << inst.rs2 << ", " << inst.imm << '\n';
		}
		else if (inst.type == TYPE_J) {
			std::cout << inst.name << " x" << inst.rd << ", " << inst.imm << '\n';
		}
		else if (inst.type == TYPE_U) {
			std::cout << inst.name << " x" << inst.rd << ", " << inst.imm << '\n';
		}
		else if (inst.type == TYPE_LOAD) {
			std::cout << inst.name << " x" << inst.rd << ", " << inst.imm << "(x" << inst.rs1 << ")" << '\n';
		}
		else if (inst.type == TYPE_JALR) {
			std::cout << inst.name << " x" << inst.rd << ", x" << inst.rs1 << ", " << inst.imm << '\n';
		}
		else if (inst.type == TYPE_ENVIRONMENT) {
			std::cout << inst.name << '\n';
		}
		else {
			std::cout << inst.type << '\n';
		}
	
	}

	return 0;
}
