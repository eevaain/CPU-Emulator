#include <iostream>
#include <cstdint>
#include <fstream>

// curly brackets for key pairs

class Chip8 {
public:
	uint8_t registers[16]{};
	uint8_t memory[4096]{};
	uint16_t indexRegister{};
	uint16_t programCounter{}; 
	uint16_t stack[16]{};
	uint8_t stackPointer{};
	uint8_t delayTimer{};
	uint8_t inputKeys[16]{};
	uint32_t displayMemory[64 * 32]{};
	uint16_t opCode{};

	Chip8(); // CONSTRUCTOR -> what does it do? why is keypad mapped to this
		void LoadROM();
		void Random();
		void Cycle();
	~Chip8(); //DESTRUCTOR

	// make structs of key:pair value "types" for opcodes

	// opcodes

};

// load in stuff using constructor (first executed instructions)


//declaring function method contents outside of class

const unsigned int START_ADDRESS = 0x200;

void Chip8::LoadROM() {

	std::ifstream





}

Chip8::Chip8() {

	// dont need a void init() cus constructor is init? 
	// set init address for interpreter
	//fontset declaration
	// so like clear registers stack and mem and everything lol incl display
	programCounter = START_ADDRESS;

}


void Chip8::Cycle() {

	// this is where opcode shit happens

}

void Chip8::Random() {

}

//declare contents of key:pairs "types" here







Chip8::~Chip8(){} //run destructor




// turn this in its own main.cpp file
int main() {

	// add clock loop here

	return 0;
}
