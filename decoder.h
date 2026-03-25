#pragma once

#include <string>
#include <cstdint>

std::string getBinary();

std::string decodeInstruction(uint32_t, uint32_t, uint32_t);

uint32_t convertBinary(const std::string&);

uint32_t getOpCode(uint32_t);

uint32_t getRd(uint32_t);

uint32_t getFunct3(uint32_t);

uint32_t getRs1(uint32_t);

int32_t getImm(uint32_t);

uint32_t getFunct7(uint32_t);

uint32_t getShamt(uint32_t);

uint32_t getRs2(uint32_t);
