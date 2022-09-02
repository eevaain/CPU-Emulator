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
	std::cout << "\nEquivalent Hex Byte: " << random_hex << std::endl << "\n";
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


void Chip8::OP_00E0() {

}