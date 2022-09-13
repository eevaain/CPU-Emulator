#include <iostream>
#include <cstdint>
#include <fstream>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include "chip8.hpp"
#include <random>
#include <chrono>

/*
USING uint automatically translates hex into binary
we use unsigned ints to know value we are storing is positive

*/

const unsigned CHIP8_FONTSET = 80;
const unsigned FONTSET_START = 0x50;
const unsigned int START_ADDRESS = 0x200; //512 dec, address 513


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


Chip8::Chip8() 

{ //constructor

	pc = START_ADDRESS; 

	// load in FONTS

	for (
		int i = 0;
		i < CHIP8_FONTSET;
		++i
		) {
		Chip8::memory[FONTSET_START + i] = fontset[i];
	}


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
		tableE_sub[0xE] = &Chip8::OP_Ex9E; //save memory instead of using 9E (E)
		tableE_sub[0x1] = &Chip8::OP_ExA1; //save memory instead of A1 (1)
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
	// TODO
	uint8_t table_index = (opcode & 0x000F);
	(this->*(table0_sub[table_index]))();
}

void Chip8::OP_00E0() {
	memset(display, 0, sizeof(display)); 
}

void Chip8::OP_00EE() {
	--sp;
	pc = stack[sp];
}

void Chip8::OP_1nnn() {
	uint16_t address = (opcode & 0x0FFF);
	pc = address; 
}

void Chip8::OP_2nnn() {
	uint16_t address = (opcode & 0x0FFF);
	stack[sp] = pc; 
	++sp;
	pc = address; 
}

void Chip8::OP_3xkk() {
	uint8_t register_index = (opcode & 0x0F00) >> 8;
	uint8_t register_value = registers[register_index];
	uint8_t address = (opcode & 0x00FF);
	
	if (register_value == address) {
		pc += 2;
	}
}

void Chip8::OP_4xkk() {
	uint8_t register_index = (opcode & 0x0F00) >> 8;
	uint8_t register_value = registers[register_index];
	uint8_t address = (opcode & 0x00FF);

	if (register_value != address) {
		pc += 2;
	}
}

void Chip8::OP_5xy0() {
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_index_y = (opcode & 0x00F0) >> 4;
	uint8_t reg_value_x = registers[reg_index_x];
	uint8_t reg_value_y = registers[reg_index_y];

	if (reg_value_x == reg_value_y) {
		pc += 2;
	}
}

void Chip8::OP_6xkk() {
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t address = (opcode & 0x00FF);
	registers[reg_index_x] = address; 
}

void Chip8::OP_7xkk() {
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t value = (opcode & 0x00FF);
	registers[reg_index_x] += value;
}

void Chip8::branchTo_Table8() {
	uint8_t table_index = (opcode & 0x000F);
	(this->*(table0_sub[table_index]))();
}

void Chip8::OP_8xy0() {
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_index_y = (opcode & 0x00F0) >> 4;
	uint8_t reg_val_y = registers[reg_index_y]; 
	registers[reg_index_x] = reg_val_y; 
}

void Chip8::OP_8xy1() {
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_index_y = (opcode & 0x00F0) >> 4;
	uint8_t reg_val_x = registers[reg_index_x];
	uint8_t reg_val_y = registers[reg_index_y];
	registers[reg_index_x] = (reg_val_x | reg_val_y); 
}

void Chip8::OP_8xy2() {
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_index_y = (opcode & 0x00F0) >> 4;
	uint8_t reg_val_x = registers[reg_index_x];
	uint8_t reg_val_y = registers[reg_index_y];
	registers[reg_index_x] = (reg_val_x & reg_val_y);
}

void Chip8::OP_8xy3() {
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_index_y = (opcode & 0x00F0) >> 4;
	uint8_t reg_val_x = registers[reg_index_x];
	uint8_t reg_val_y = registers[reg_index_y];
	registers[reg_index_x] = (reg_val_x ^ reg_val_y);
}

void Chip8::OP_8xy4() {
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_index_y = (opcode & 0x00F0) >> 4;
	uint8_t reg_val_x = registers[reg_index_x];
	uint8_t reg_val_y = registers[reg_index_y];
	uint16_t addition = reg_val_x + reg_val_y; 

	if (addition > 255) {
		registers[0xF] = 1; 
	}
	else {
		registers[0xF] = 0;
	}
	registers[reg_index_x] = (addition & 0x00FF);
}

void Chip8::OP_8xy5() { //double check
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_index_y = (opcode & 0x00F0) >> 4;
	uint8_t reg_val_x = registers[reg_index_x];
	uint8_t reg_val_y = registers[reg_index_y];

	if (reg_val_x > reg_val_y) {
		registers[0xF] = 1;
	}
	else {
		registers[0xF] = 0;
	}
	registers[reg_index_x] = reg_val_x - reg_val_y;
}

void Chip8::OP_8xy6() { //double check (this is least significant bit) 
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_val_x = registers[reg_index_x];

	if ((reg_val_x & 0x1) == 1) { // least sig bit
		registers[0xF] = 1;
	}
	else {
		registers[0xF] = 0;
	}
	registers[reg_index_x] = (reg_val_x >> 1); 
}

void Chip8::OP_8xy7() { //double check... wait nvm this one looks pretty accurate
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_index_y = (opcode & 0x00F0) >> 4;
	uint8_t reg_val_x = registers[reg_index_x];
	uint8_t reg_val_y = registers[reg_index_y];

	if (reg_val_y > reg_val_x) {
		registers[0xF] = 1;
	}
	else {
		registers[0xF] = 0;
	}
	registers[reg_index_x] = reg_val_y - reg_val_x; 
}

void Chip8::OP_8xyE() { // double check this is most significant bit
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_val_x = registers[reg_index_x];

	if (((reg_val_x & 0x80) >> 7) == 1) { // most sig bit
		registers[0xF] = 1;
	}
	else {
		registers[0xF] = 0;
	}
	registers[reg_index_x] = (reg_val_x << 1); 
}

void Chip8::OP_9xy0() {
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t reg_index_y = (opcode & 0x00F0) >> 4;
	uint8_t reg_val_x = registers[reg_index_x];
	uint8_t reg_val_y = registers[reg_index_y];

	if (reg_val_x != reg_val_y) {
		pc += 2; 
	}
}

void Chip8::OP_Annn() {
	uint16_t set_address = (opcode & 0x0FFF); 
	index = set_address;
}

void Chip8::OP_Bnnn() {
	uint16_t set_address = (opcode & 0x0FFF);
	pc = (set_address + registers[0]);
}

void Chip8::OP_Cxkk() {
	uint8_t reg_index_x = (opcode & 0x0F00) >> 8;
	uint8_t set_address = (opcode & 0x00FF);

	//gotta fix this random thing
	srand(time(NULL));
	// Get a random number
	int random = (rand() % 255);
	// Print the random number
	std::cout << random << std::endl;

	registers[reg_index_x] = (set_address & random); 
}

void Chip8::OP_Dxyn() { // NOT MY CODE
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (opcode & 0x00F0u) >> 4u;
	uint8_t height = opcode & 0x000Fu;

	// Wrap if going beyond screen boundaries
	uint8_t xPos = registers[Vx] % VIDEO_WIDTH;
	uint8_t yPos = registers[Vy] % VIDEO_HEIGHT;

	registers[0xF] = 0;

	for (unsigned int row = 0; row < height; ++row)
	{
		uint8_t spriteByte = memory[index + row];

		for (unsigned int col = 0; col < 8; ++col)
		{
			uint8_t spritePixel = spriteByte & (0x80u >> col);
			uint32_t* screenPixel = &display[(yPos + row) * VIDEO_WIDTH + (xPos + col)];

			// Sprite pixel is on
			if (spritePixel)
			{
				// Screen pixel also on - collision
				if (*screenPixel == 0xFFFFFFFF)
				{
					registers[0xF] = 1;
				}

				// Effectively XOR with the sprite pixel
				*screenPixel ^= 0xFFFFFFFF;
			}
		}
	}

}

void Chip8::branchTo_TableE() {
	uint8_t table_index = (opcode & 0x000F);
	(this->*(table0_sub[table_index]))();
}

void Chip8::OP_Ex9E() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	uint8_t key = registers[Vx];

	if (keypad[key])
	{
		pc += 2;
	}
}

void Chip8::OP_ExA1() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	uint8_t key = registers[Vx];

	if (!keypad[key])
	{
		pc += 2;
	}
}

void Chip8::branchTo_TableF() {
	uint8_t table_index = (opcode & 0x000F);
	(this->*(table0_sub[table_index]))();

}

void Chip8::OP_Fx07() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	registers[Vx] = delayTimer;
}

void Chip8::OP_Fx0A() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	if (keypad[0])
	{
		registers[Vx] = 0;
	}
	else if (keypad[1])
	{
		registers[Vx] = 1;
	}
	else if (keypad[2])
	{
		registers[Vx] = 2;
	}
	else if (keypad[3])
	{
		registers[Vx] = 3;
	}
	else if (keypad[4])
	{
		registers[Vx] = 4;
	}
	else if (keypad[5])
	{
		registers[Vx] = 5;
	}
	else if (keypad[6])
	{
		registers[Vx] = 6;
	}
	else if (keypad[7])
	{
		registers[Vx] = 7;
	}
	else if (keypad[8])
	{
		registers[Vx] = 8;
	}
	else if (keypad[9])
	{
		registers[Vx] = 9;
	}
	else if (keypad[10])
	{
		registers[Vx] = 10;
	}
	else if (keypad[11])
	{
		registers[Vx] = 11;
	}
	else if (keypad[12])
	{
		registers[Vx] = 12;
	}
	else if (keypad[13])
	{
		registers[Vx] = 13;
	}
	else if (keypad[14])
	{
		registers[Vx] = 14;
	}
	else if (keypad[15])
	{
		registers[Vx] = 15;
	}
	else
	{
		pc -= 2;
	}
}

void Chip8::OP_Fx15() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	delayTimer = registers[Vx];

}

void Chip8::OP_Fx18() {

	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	soundTimer = registers[Vx];
}

void Chip8::OP_Fx1E() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	index += registers[Vx];

}

void Chip8::OP_Fx29() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t digit = registers[Vx];

	index = FONTSET_START + (5 * digit);

}


void Chip8::OP_Fx33() {

	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t value = registers[Vx];

	// Ones-place
	memory[index + 2] = value % 10;
	value /= 10;

	// Tens-place
	memory[index + 1] = value % 10;
	value /= 10;

	// Hundreds-place
	memory[index] = value % 10;
}

void Chip8::OP_Fx55() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= Vx; ++i)
	{
		memory[index + i] = registers[i];
	}

}

void Chip8::OP_Fx65() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= Vx; ++i)
	{
		registers[i] = memory[index + i];
	}

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
	
	//some opcode decoding fetching from rom and parseing it through bitwise oper.
	//program couner increment before execution

		// Fetch
	opcode = (memory[pc] << 8u) | memory[pc + 1];

	// Increment the PC before we execute anything
	pc += 2;

	// Decode and Execute
	((*this).*(tableParent[(opcode & 0xF000u) >> 12u]))();

	// Decrement the delay timer if it's been set
	if (delayTimer > 0)
	{
		--delayTimer;
	}

	// Decrement the sound timer if it's been set
	if (soundTimer > 0)
	{
		--soundTimer;
	}

}

Chip8::~Chip8() {}

