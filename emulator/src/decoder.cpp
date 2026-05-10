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

int32_t getUpperImm(uint32_t value) {
	uint32_t imm = value & 0xFFFFF000;

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

uint32_t getFunct5(uint32_t value) {
	uint32_t funct5 = (value >> 27) & 0x1F;

	return funct5;
}

uint32_t getFmt(uint32_t value) {
	uint32_t fmt = (value >> 25) & 0x3;

	return fmt;
}

uint32_t getRm(uint32_t value) {
	uint32_t funct3 = (value >> 12) & 0x7;

	return funct3;
}

uint32_t getRs3(uint32_t value) {
	uint32_t rs3 = (value >> 27) & 0x1F;

	return rs3;
}

std::string instructionToString(Instruction inst) {
	switch (inst) {
		// Immediate Arithmetic
	case Instruction::ADDI:   return "addi";
	case Instruction::ANDI:   return "andi";
	case Instruction::ORI:    return "ori";
	case Instruction::XORI:   return "xori";
	case Instruction::SLTI:   return "slti";
	case Instruction::SLTIU:  return "sltiu";

		// Immediate Shifts
	case Instruction::SLLI:   return "slli";
	case Instruction::SRLI:   return "srli";
	case Instruction::SRAI:   return "srai";

		// Register-Register Arithmetic
	case Instruction::ADD:    return "add";
	case Instruction::SUB:    return "sub";
	case Instruction::AND:    return "and";
	case Instruction::OR:     return "or";
	case Instruction::XOR:    return "xor";
	case Instruction::SLL:    return "sll";
	case Instruction::SRL:    return "srl";
	case Instruction::SRA:    return "sra";
	case Instruction::SLT:    return "slt";
	case Instruction::SLTU:   return "sltu";

		// Stores
	case Instruction::SB:     return "sb";
	case Instruction::SH:     return "sh";
	case Instruction::SW:     return "sw";

		// Loads
	case Instruction::LB:     return "lb";
	case Instruction::LBU:    return "lbu";
	case Instruction::LH:     return "lh";
	case Instruction::LHU:    return "lhu";
	case Instruction::LW:     return "lw";;

		// Branches
	case Instruction::BEQ:    return "beq";
	case Instruction::BNE:    return "bne";
	case Instruction::BLT:    return "blt";
	case Instruction::BLTU:   return "bltu";
	case Instruction::BGE:    return "bge";
	case Instruction::BGEU:   return "bgeu";

		// Jumps & Upper Immediates
	case Instruction::JAL:    return "jal";
	case Instruction::JALR:   return "jalr";
	case Instruction::LUI:    return "lui";
	case Instruction::AUIPC:  return "auipc";

		// M-Extension (Multiply/Divide)
	case Instruction::MUL:    return "mul";
	case Instruction::MULH:   return "mulh";
	case Instruction::MULHSU: return "mulhsu";
	case Instruction::MULHU:  return "mulhu";
	case Instruction::DIV:    return "div";
	case Instruction::DIVU:   return "divu";
	case Instruction::REM:    return "rem";
	case Instruction::REMU:   return "remu";

		// FP Load
	case Instruction::FLW: return "flw";

		// FP Store
	case Instruction::FSW: return "fsw";

		// FP Arithmetic Instructions
	case Instruction::FADDS: return "fadd.s";
	case Instruction::FMULS: return "fmul.s";
	case Instruction::FSUBS: return "fsub.s";
	case Instruction::FDIVS: return "fdiv.s";
	case Instruction::FSGNJS: return "fsgnj.s";
	case Instruction::FSGNJNS: return "fsgnjn.s";
	case Instruction::FSGNJXS: return "fsgnjx.s";

		// FP With One Register
	case Instruction::FSQRT: return "fsqrt";

		// FP MIN/MAX
	case Instruction::FMIN: return "fmin";
	case Instruction::FMAX: return "fmax";

		// FP R-4 Type
	case Instruction::FMADDS: return "fmadd.s";
	case Instruction::FMSUBS: return "fmsub.s";
	case Instruction::FNMSUBS: return "fnmsub.s";
	case Instruction::FNMADDS: return "fnmadd.s";

		// FP REG to Int Reg
	case Instruction::FCVTWS: return "fcvt.w.s";
	case Instruction::FCVTWUS: return "fcvt.wu.s";
	case Instruction::FMVXW: return "fmv.x.w";
	case Instruction::FCLASSS: return "fclass.s";

		// Int Reg to FP Reg
	case Instruction::FCVTSW: return "fcvt.s.w";
	case Instruction::FCVTSWU: return "fcvt.s.wu";
	case Instruction::FMVWX: return "fmv.w.x";

		// FP Comparison Instructions
	case Instruction::FEQS: return "feq.s";
	case Instruction::FLTS: return "flt.s";
	case Instruction::FLES: return "fle.s";

		// System
	case Instruction::ECALL:  return "ecall";
	case Instruction::EBREAK: return "ebreak";

		// Default
	case Instruction::UNKNOWN:
	default:                  return "unknown";
	}
}

DecodedInstruction decodeInstruction(uint32_t value) {
	DecodedInstruction inst{};

	uint32_t opcode{ getOpCode(value) };
	uint32_t funct3{ getFunct3(value) };
	uint32_t funct7{ getFunct7(value) };
	uint32_t funct5{ getFunct5(value) };
	uint32_t rm{ getRm(value) };

	switch (opcode) {
	case 0x33:
		inst.type = InstructionType::R;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);

		switch (funct3) {
		case 0x0:
			if (funct7 == 0x0) inst.name = Instruction::ADD;
			else if (funct7 == 0x20) inst.name = Instruction::SUB;
			else if (funct7 == 0x1) inst.name = Instruction::MUL;
			break;
		case 0x7:
			if (funct7 == 0x0) inst.name = Instruction::AND;
			else if (funct7 == 0x1) inst.name = Instruction::REMU;
			break;
		case 0x6:
			if (funct7 == 0x0) inst.name = Instruction::OR;
			else if (funct7 == 0x1) inst.name = Instruction::REM;
			break;
		case 0x4:
			if (funct7 == 0x0) inst.name = Instruction::XOR;
			else if (funct7 == 0x1) inst.name = Instruction::DIV;
			break;
		case 0x1:
			if (funct7 == 0x0) inst.name = Instruction::SLL;
			else if (funct7 == 0x1) inst.name = Instruction::MULH;
			break;
		case 0x5:
			if (funct7 == 0x0) inst.name = Instruction::SRL;
			else if (funct7 == 0x20) inst.name = Instruction::SRA;
			else if (funct7 == 0x1) inst.name = Instruction::DIVU;
			break;
		case 0x2:
			if (funct7 == 0x0) inst.name = Instruction::SLT;
			else if (funct7 == 0x1) inst.name = Instruction::MULHSU;
			break;
		case 0x3:
			if (funct7 == 0x0) inst.name = Instruction::SLTU;
			else if (funct7 == 0x1) inst.name = Instruction::MULHU;
			break;
		}
		break;

	case 0x13:
		inst.type = InstructionType::I;
		inst.rd = getRd(value);
		inst.rs1 = getRs1(value);

		switch (funct3) {
		case 0x0:
			inst.name = Instruction::ADDI;
			inst.imm = getImm(value);
			break;
		case 0x7:
			inst.name = Instruction::ANDI;
			inst.imm = getImm(value);
			break;
		case 0x6:
			inst.name = Instruction::ORI;
			inst.imm = getImm(value);
			break;
		case 0x4:
			inst.name = Instruction::XORI;
			inst.imm = getImm(value);
			break;
		case 0x2:
			inst.name = Instruction::SLTI;
			inst.imm = getImm(value);
			break;
		case 0x3:
			inst.name = Instruction::SLTIU;
			inst.imm = getImm(value);
			break;
		case 0x1:
			if (funct7 == 0x0) {
				inst.type = InstructionType::SHIFT;
				inst.name = Instruction::SLLI;
				inst.shamt = getShamt(value);
			}
			break;
		case 0x5:
			if (funct7 == 0x0) {
				inst.type = InstructionType::SHIFT;
				inst.name = Instruction::SRLI;
				inst.shamt = getShamt(value);
			}
			else if (funct7 == 0x20) {
				inst.type = InstructionType::SHIFT;
				inst.name = Instruction::SRAI;
				inst.shamt = getShamt(value);
			}
			break;
		}
		break;

	case 0x23:
		inst.type = InstructionType::S;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getStoreImm(value);
		switch (funct3) {
		case 0x0:
			inst.name = Instruction::SB;
			break;
		case 0x1:
			inst.name = Instruction::SH;
			break;
		case 0x2:
			inst.name = Instruction::SW;
			break;
		}
		break;

	case 0x63:
		inst.type = InstructionType::B;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getBranchImm(value);
		switch (funct3) {
		case 0x0:
			inst.name = Instruction::BEQ;
			break;
		case 0x1:
			inst.name = Instruction::BNE;
			break;
		case 0x4:
			inst.name = Instruction::BLT;
			break;
		case 0x6:
			inst.name = Instruction::BLTU;
			break;
		case 0x5:
			inst.name = Instruction::BGE;
			break;
		case 0x7:
			inst.name = Instruction::BGEU;
			break;
		}
		break;

	case 0x6F:
		inst.name = Instruction::JAL;
		inst.type = InstructionType::J;
		inst.rd = getRd(value);
		inst.imm = getJalImm(value);
		break;

	case 0x37:
		inst.name = Instruction::LUI;
		inst.type = InstructionType::U;
		inst.rd = getRd(value);
		inst.imm = getUpperImm(value);
		break;

	case 0x17:
		inst.name = Instruction::AUIPC;
		inst.type = InstructionType::U;
		inst.rd = getRd(value);
		inst.imm = getUpperImm(value);
		break;

	case 0x3:
		inst.type = InstructionType::LOAD;
		inst.rs1 = getRs1(value);
		inst.rd = getRd(value);
		inst.imm = getImm(value);
		switch (funct3) {
		case 0x0:
			inst.name = Instruction::LB;
			break;
		case 0x4:
			inst.name = Instruction::LBU;
			break;
		case 0x1:
			inst.name = Instruction::LH;
			break;
		case 0x5:
			inst.name = Instruction::LHU;
			break;
		case 0x2:
			inst.name = Instruction::LW;
			break;
		}
		break;

	case 0x67:
		inst.name = Instruction::JALR;
		inst.type = InstructionType::JALR;
		inst.rs1 = getRs1(value);
		inst.rd = getRd(value);
		inst.imm = getImm(value);
		break;

	case 0x7:
		inst.name = Instruction::FLW;
		inst.type = InstructionType::FPL;
		inst.rs1 = getRs1(value);
		inst.rd = getRd(value);
		inst.imm = getImm(value);
		break;

	case 0x27:
		inst.name = Instruction::FSW;
		inst.type = InstructionType::FPS;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.imm = getStoreImm(value);
		break;

	case 0x53:
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.rd = getRd(value);
		inst.fmt = getFmt(value);

		switch (funct5) {
		case 0x0:
			inst.name = Instruction::FADDS;
			inst.type = InstructionType::FPA;
			break;
		case 0x2:
			inst.name = Instruction::FMULS;
			inst.type = InstructionType::FPA;
			break;
		case 0x1:
			inst.name = Instruction::FSUBS;
			inst.type = InstructionType::FPA;
			break;
		case 0x3:
			inst.name = Instruction::FDIVS;
			inst.type = InstructionType::FPA;
			break;
		case 0xB:
			inst.name = Instruction::FSQRT;
			inst.type = InstructionType::FPR1;
			break;
		case 0x5:
			if (rm == 0x0) {
				inst.name = Instruction::FMIN;
				inst.type = InstructionType::FMINMAX;
			}
			else if (rm == 0x1) {
				inst.name = Instruction::FMAX;
				inst.type = InstructionType::FMINMAX;
			}
			break;
		case 0x18:
			if (inst.rs2 == 0x0) {
				inst.name = Instruction::FCVTWS;
				inst.type = InstructionType::FPCONVINT;
			}
			else if (inst.rs2 == 0x1) {
				inst.name = Instruction::FCVTWUS;
				inst.type = InstructionType::FPCONVINT;
			}
			break;
		case 0x1A:
			if (inst.rs2 == 0x0) {
				inst.name = Instruction::FCVTSW;
				inst.type = InstructionType::INTCONVFP;
			}
			else if (inst.rs2 == 0x1) {
				inst.name = Instruction::FCVTSWU;
				inst.type = InstructionType::INTCONVFP;
			}
			break;
		case 0x4:
			if (rm == 0x0) {
				inst.name = Instruction::FSGNJS;
				inst.type = InstructionType::FPA;
			}
			else if (rm == 0x1) {
				inst.name = Instruction::FSGNJNS;
				inst.type = InstructionType::FPA;
			}
			else if (rm == 0x2) {
				inst.name = Instruction::FSGNJXS;
				inst.type = InstructionType::FPA;
			}
			break;
		case 0x1C:
			if (rm == 0x0) {
				inst.name = Instruction::FMVXW;
				inst.type = InstructionType::FPCONVINT;
			}
			else if (rm == 0x1) {
				inst.name = Instruction::FCLASSS;
				inst.type = InstructionType::FPCONVINT;
			}
			break;
		case 0x1E:
			inst.name = Instruction::FMVWX;
			inst.type = InstructionType::INTCONVFP;
			break;
		case 0x14:
			if (rm == 0x0) {
				inst.name = Instruction::FLES;
				inst.type = InstructionType::FCOMP;
			}
			else if (rm == 0x1) {
				inst.name = Instruction::FLTS;
				inst.type = InstructionType::FCOMP;
			}
			else if (rm == 0x2) {
				inst.name = Instruction::FEQS;
				inst.type = InstructionType::FCOMP;
			}
			break;
		}
		break;

	case 0x43:
		inst.name = Instruction::FMADDS;
		inst.type = InstructionType::FPR4;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.rs3 = getRs3(value);
		inst.rd = getRd(value);
		inst.fmt = getFmt(value);
		break;

	case 0x47:
		inst.name = Instruction::FMSUBS;
		inst.type = InstructionType::FPR4;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.rs3 = getRs3(value);
		inst.rd = getRd(value);
		inst.fmt = getFmt(value);
		break;

	case 0x4B:
		inst.name = Instruction::FNMSUBS;
		inst.type = InstructionType::FPR4;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.rs3 = getRs3(value);
		inst.rd = getRd(value);
		inst.fmt = getFmt(value);
		break;

	case 0x4F:
		inst.name = Instruction::FNMADDS;
		inst.type = InstructionType::FPR4;
		inst.rs1 = getRs1(value);
		inst.rs2 = getRs2(value);
		inst.rs3 = getRs3(value);
		inst.rd = getRd(value);
		inst.fmt = getFmt(value);
		break;

	case 0x73: {
		uint32_t funct12 = (value >> 20) & 0xFFF;
		inst.type = InstructionType::ENVIRONMENT;
		switch (funct3) {
		case 0x0:
			if (funct12 == 0x1) inst.name = Instruction::EBREAK;
			else if (funct12 == 0x0) inst.name = Instruction::ECALL;
			break;
		}
		break;
	}

	default:
		inst.name = Instruction::UNKNOWN;
		inst.type = InstructionType::UNKNOWN;
	}

	return inst;
}
