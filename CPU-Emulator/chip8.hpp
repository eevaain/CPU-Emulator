#pragma once

#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


class Chip8 {
public:
	Chip8();
	~Chip8();
	void loadROM(char const* filename);
	void Cycle();
	// maybe move keypad here
	// maybe move video here
private:
	uint8_t registers[16]{};
	uint8_t memory[4096]{};
	uint16_t index{};
	uint16_t pc{};
	uint16_t stack[16]{};
	uint8_t sp{};
	uint8_t delayTimer{};
	uint8_t soundTimer{};
	uint8_t keys[16]{};
	uint32_t display[64 * 32]{};
	uint16_t opCode{};

	typedef void (Chip8::*memAddressSpace)();
	memAddressSpace tableParent[0xF + 1];		//single parse opcodes or... 
									//branching to 2nd parsing functions
		memAddressSpace table0_sub[0xE + 1];
		memAddressSpace table8_sub[0xE + 1];
		memAddressSpace tableE_sub[0xE + 1];
		memAddressSpace tableF_sub[0x65 + 1];

	void branchTo_Table0(); //0
		void OP_00E0();
		void OP_00EE();
	void OP_1nnn(); //1
	void OP_2nnn(); //2
	void OP_3xkk(); //3
	void OP_4xkk(); //4
	void OP_5xy0(); //5
	void OP_6xkk(); //6
	void OP_7xkk(); //7 
	void branchTo_Table8(); //8
		void OP_8xy0();
		void OP_8xy1();
		void OP_8xy2();
		void OP_8xy3();
		void OP_8xy4();
		void OP_8xy5();
		void OP_8xy6();
		void OP_8xy7();
		void OP_8xyE();
	void OP_9xy0(); //9
	void OP_Annn(); //A
	void OP_Bnnn(); //B
	void OP_Cxkk(); //C
	void OP_Dxyn(); //D
	void branchTo_TableE(); //E
		void OP_Ex9E();
		void OP_ExA1();
	void branchTo_TableF(); //F
		void OP_Fx07();
		void OP_Fx0A();
		void OP_Fx15();
		void OP_Fx18();
		void OP_Fx1E();
		void OP_Fx29();
		void OP_Fx33();
		void OP_Fx55();
		void OP_Fx65();

};