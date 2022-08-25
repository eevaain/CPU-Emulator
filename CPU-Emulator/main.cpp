#include <iostream>
#include <cstdint>

// curly brackets for key pairs

class Chip8 {
public:
	uint8_t registers[16];
	uint8_t memory[4000];
	uint16_t indexRegister{};
	uint16_t programCounter{}; 
	uint16_t stack[16];
	uint8_t stackPointer{};
	uint8_t delayTimer{};
	uint8_t inputKeys[16];
	uint32_t displayMemory[64 * 32];
	uint16_t classMembers{};

};


// uint8_t


int main() {

	// add clock loop here

	return 0;
}
