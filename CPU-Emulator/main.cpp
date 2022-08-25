#include <iostream>
#include <cstdint>

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
		void Cycle();
		void LoadROM(); 
		void Random();
	~Chip8(); //DESTRUCTOR

	// make structs of key:pair value "types" for opcodes

	// opcodes

};

// load in stuff using constructor
Chip8::Chip8() {
	//fontset declaration

	// so like clear registers stack and mem and everything lol incl display

}


//declaring function method contents outside of class
void Chip8::Cycle() {

}

void Chip8::LoadROM() {

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
