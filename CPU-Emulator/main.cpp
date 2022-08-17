#include <iostream>
#include <cstdint>

// curly brackets for key pairs

class Chip8 {
public:
	uint8_t registers[16];
	uint8_t memory[4000];
	uint16_t index_register{};
	uint16_t program_counter{}; 
	uint16_t stack[16];

};


// uint8_t


int main() {

	// add clock loop here

	return 0;
}
