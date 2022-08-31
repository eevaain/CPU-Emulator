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

	uint8_t registers[16]{};
	uint8_t memory[4096]{};
	uint16_t ir{};
	uint16_t pc{};
	uint16_t stack[16]{};
	uint8_t sp{};
	uint8_t delayTimer{};
	uint8_t keys[16]{};
	uint32_t display[64 * 32]{};
	uint16_t opCode{};
	void loadROM(char const* filename);
	void Cycle();




};