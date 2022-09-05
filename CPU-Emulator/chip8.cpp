#include <iostream>
#include <cstdint>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chip8.hpp"
#include <random>

/*
USING uint automatically translates hex into binary
we use unsigned ints to know value we are storing is positive

*/

const unsigned int START_ADDRESS = 0x200; //512 dec, address 513


Chip8::Chip8() { //constructor

	pc = START_ADDRESS; 

	// load in FONTS
	
	const unsigned CHIP8_FONTSET = 80;

	uint8_t fontset[CHIP8_FONTSET] = {
			0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
			0x20, 0x60, 0x20, 0x20, 0x70, // 1
			0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
			0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
			0x90, 0x90, 0xF0, 0x10, 0x10, // 4
			0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
			0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
			0xF0, 0x10, 0x20, 0x40, 0x40, // 7
			0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
			0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
			0xF0, 0x90, 0xF0, 0x90, 0x90, // A
			0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
			0xF0, 0x80, 0x80, 0x80, 0xF0, // C
			0xE0, 0x90, 0x90, 0x90, 0xE0, // D
			0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
			0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	const unsigned FONTSET_START = 0x50;

	for (
		int i = 0;
		i < CHIP8_FONTSET;
		++i
		) {
		Chip8::memory[FONTSET_START + i] = fontset[i];
	}

	//RNG
	const int MAX_N = 255;
	const int min_n = 0;
	char random_hex[MAX_N];
	int new_n;
	new_n = (rand() % MAX_N);
	_itoa_s(new_n, random_hex, 16); // converts dec to hex
	std::cout << "\n Random Equivalent Hex Byte: " << random_hex << std::endl << "\n";


	// load in functions for parent array
	tableParent[0x0] = &Chip8::branchTo_Table0; //0
		table0_sub[0x0] = &Chip8::OP_00E0;
		table0_sub[0xE] = &Chip8::OP_00EE;
	tableParent[0x1] = &Chip8::OP_1nnn; //1
	tableParent[0x2] = &Chip8::OP_2nnn; //2
	tableParent[0x3] = &Chip8::OP_3xkk; //3
	tableParent[0x4] = &Chip8::OP_4xkk; //4
	tableParent[0x5] = &Chip8::OP_5xy0; //5
	tableParent[0x6] = &Chip8::OP_6xkk; //6
	tableParent[0x7] = &Chip8::OP_7xkk; //7
	tableParent[0x8] = &Chip8::branchTo_Table8; //8
		table8_sub[0x0] = &Chip8::OP_8xy0;
		table8_sub[0x1] = &Chip8::OP_8xy1;
		table8_sub[0x2] = &Chip8::OP_8xy2;
		table8_sub[0x3] = &Chip8::OP_8xy3;
		table8_sub[0x4] = &Chip8::OP_8xy4;
		table8_sub[0x5] = &Chip8::OP_8xy5;
		table8_sub[0x6] = &Chip8::OP_8xy6;
		table8_sub[0x7] = &Chip8::OP_8xy7;
		table8_sub[0xE] = &Chip8::OP_8xyE;
	tableParent[0x9] = &Chip8::OP_9xy0; //9
	tableParent[0xA] = &Chip8::OP_Annn; //A
	tableParent[0xB] = &Chip8::OP_Bnnn; //B
	tableParent[0xC] = &Chip8::OP_Cxkk; //C
	tableParent[0xD] = &Chip8::OP_Dxyn; //D
	tableParent[0xE] = &Chip8::branchTo_TableE; //E
		tableE_sub[0x9E] = &Chip8::OP_Ex9E;
		tableE_sub[0xA1] = &Chip8::OP_ExA1;
	tableParent[0xF] = &Chip8::branchTo_TableF; //F
	tableF_sub[0x07] = &Chip8::OP_Fx07;
	tableF_sub[0x0A] = &Chip8::OP_Fx0A;
	tableF_sub[0x15] = &Chip8::OP_Fx15;
	tableF_sub[0x18] = &Chip8::OP_Fx18;
	tableF_sub[0x1E] = &Chip8::OP_Fx1E;
	tableF_sub[0x29] = &Chip8::OP_Fx29;
	tableF_sub[0x33] = &Chip8::OP_Fx33;
	tableF_sub[0x55] = &Chip8::OP_Fx55;
	tableF_sub[0x65] = &Chip8::OP_Fx65;

}

// function definitions

void Chip8::branchTo_Table0() {


}

void Chip8::OP_00E0() {


}

void Chip8::OP_00EE() {


}

void Chip8::OP_1nnn() {


}

void Chip8::OP_2nnn() {


}

void Chip8::OP_3xkk() {


}

void Chip8::OP_4xkk() {


}

void Chip8::OP_5xy0() {


}

void Chip8::OP_6xkk() {


}

void Chip8::OP_7xkk() {


}

void Chip8::branchTo_Table8() {


}

void Chip8::OP_8xy0() {


}

void Chip8::OP_8xy1() {


}

void Chip8::OP_8xy2() {


}

void Chip8::OP_8xy3() {


}

void Chip8::OP_8xy4() {


}

void Chip8::OP_8xy5() {


}

void Chip8::OP_8xy6() {


}

void Chip8::OP_8xy7() {


}

void Chip8::OP_8xyE() {


}

void Chip8::OP_9xy0() {


}

void Chip8::OP_Annn() {


}

void Chip8::OP_Bnnn() {


}

void Chip8::OP_Cxkk() {


}

void Chip8::OP_Dxyn() {


}

void Chip8::branchTo_TableE() {


}

void Chip8::OP_Ex9E() {


}

void Chip8::OP_ExA1() {


}

void Chip8::branchTo_TableF() {


}

void Chip8::OP_Fx07() {


}

void Chip8::OP_Fx0A() {


}

void Chip8::OP_Fx15() {


}

void Chip8::OP_Fx18() {


}

void Chip8::OP_Fx1E() {


}

void Chip8::OP_Fx29() {


}


void Chip8::OP_Fx33() {


}

void Chip8::OP_Fx55() {


}

void Chip8::OP_Fx65() {


}


void Chip8::loadROM(char const* filename) { 
// filename represents address of an array of bytes where read elements are stored

	std::streampos size;
	char* memblock; //create buffer to store ROM 

	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate); // pointer is at end of file
	if (file.is_open()) {
		size = file.tellg();
		memblock = new char[size];			   // obtain size of file
		file.seekg(0, std::ios::beg); // position at start of file
		file.read(memblock, size); 
		file.close();

		std::cout << "ROM is stored in memory";

		for (
			long i = 0;
			i < size;
			++i
			) {
			Chip8::memory[START_ADDRESS + i] = memblock[i];
		}

		delete[] memblock;
	}
	else std::cout << "Error, unable to open ROM text file.";
}


void Chip8::Cycle() {

}

Chip8::~Chip8() {}

