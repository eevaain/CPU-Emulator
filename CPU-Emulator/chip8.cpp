#include <iostream>
#include <cstdint>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chip8.hpp"




Chip8::Chip8() {

	// load in FONTS
	//RNG

}

void Chip8::loadROM(char const* filename) { 
// filename represents address of an array of bytes where read elements are stored

	const unsigned int START_ADDRESS = 0x200;

	std::streampos size;
	char* memblock; //create buffer to store ROM 

	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()) {
		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();

		std::cout << "ROM is stored in memory";





		delete[] memblock;
	}
	else std::cout << "Error, unable to open ROM text file.";

}


void Chip8::Cycle() {

}





Chip8::~Chip8() {}
