#include "include/operations.h"
#include<memory>
#include<iostream>
_8086_Operations::_8086_Operations(memory* m, Decoder* d) :mem(m), decoder(d) {
	Ds = 0;

	for (auto& i : _16bitRegArray) {
		i = 0;
	};
	for (auto& i : _8bitRegArray) {
		i = 0;
	};
}
//conditonal statement hell 
bool _8086_Operations::performOperation(int Opcode, std::vector<std::string> line) {
	std::vector<std::string> parts = string_split_by_delimiter(line[1], ',');
	if (Opcode == 111) {// reg to reg mov
		int reg1 = whichReg(parts[0]);
		int reg2 = whichReg(parts[1]);
		copyReg(reg1, reg2);
		return true;
	}
	if (Opcode == 112) { // mem to reg mov
		
		int reg1 = whichReg(parts[0]);
		int addr = getCellAddress(parts[1]);
		uint8_t  data = getDataFromMemory(Ds, addr);
		mov8bitDataintoReg(reg1, data);
		return true;

	}
	if (Opcode == 121) { // reg to mem
		int celladdr = getCellAddress(parts[0]);
		int reg1 = whichReg(parts[1]);
		uint8_t data = _8bitRegArray[reg1];

		writeDataToMemory(Ds, celladdr, data);
		std::cout << "Debug" << reg1 << " " << (unsigned)data << " " << celladdr << "\n";
	}
	if (Opcode == 113) { // immediate data to reg
		int reg1 = whichReg(parts[0]);
		if (reg1 > 4) {
			uint8_t intData = std::stoi(parts[1]);
			_8bitRegArray[reg1] = intData;
		}
		else {
			uint16_t intData = std::stoi(parts[1]);
			_16bitRegArray[reg1] = intData;

		}
		/*	uint8_t  data = static_cast<uint8_t>(intData);*/


		return true;
	}

	if (Opcode > 200 && Opcode < 600) {
		int typeOfOperation = Opcode % 100;
		int operation = Opcode / 100;
		if (typeOfOperation == 11) {

			int reg1 = whichReg(parts[0]);
			int reg2 = whichReg(parts[1]);
			int rcode = registerPair(reg1, reg2); // gives 16 bit or 8bit reg pair
			if (rcode == 11) {
				_16bitRegArray[reg1] = _16bitArithmeticOperations(operation, reg1, reg2, false, false);
			}
			if (rcode == 12) {
				_16bitRegArray[reg1] = _16bitArithmeticOperations(operation, reg1, reg2, false, false);

			}
			if (rcode == 22) {
				_8bitRegArray[reg1] = _8bitArithmeticOperations(operation, reg1, reg2, false, false);
			}
		}
		if (typeOfOperation == 12) {
			int reg1 = whichReg(parts[0]);
			int celladd = getCellAddress(parts[1]);
			if (reg1 > 4) {
				_8bitRegArray[reg1] = _8bitArithmeticOperations(operation, reg1, celladd, true, false);
			}
			else {
				_16bitRegArray[reg1] = _16bitArithmeticOperations(operation, reg1, celladd, true, false);
			}

		}
		if (typeOfOperation == 13) {
			int reg1 = whichReg(parts[0]);
			int data = std::stoi(parts[1]);
			if (reg1 > 4) {
				_8bitRegArray[reg1] = _8bitArithmeticOperations(operation, reg1, data, false, true);
			}
			else {
				_16bitRegArray[reg1] = _16bitArithmeticOperations(operation, reg1, data, false, true);
			}
		}

	}



	return false;
}

int _8086_Operations::whichReg(std::string data) {
	if (data == "DS" || data == "Ds" || data == "ds") {
		return 0;
	}
	if (data == "AX" || data == "Ax" || data == "ax") {
		return 1;
	}
	if (data == "BX" || data == "Bx" || data == "bx") {
		return 2;
	}
	if (data == "CX" || data == "Cx" || data == "cx") {
		return 3;
	}
	if (data == "DX" || data == "Dx" || data == "dx") {
		return 4;
	}
	//8bit registers

	if (data == "AH" || data == "Ah" || data == "ah") {
		return 5;
	}
	if (data == "AL" || data == "Al" || data == "al") {
		return 6;
	}

	if (data == "BH" || data == "Bh" || data == "bh") {
		return 7;
	}
	if (data == "BL" || data == "Bl" || data == "bl") {
		return 8;
	}

	if (data == "CH" || data == "Ch" || data == "ch") {
		return 9;
	}
	if (data == "CL" || data == "Cl" || data == "cl") {
		return 10;
	}

	if (data == "DH" || data == "Dh" || data == "dh") {
		return 11;
	}
	if (data == "DL" || data == "Dl" || data == "dl") {
		return 12;
	}

	return 0;

}

bool _8086_Operations::mov8bitDataintoReg(int reg, uint8_t data) { // mov 8 bit into register

	if (reg > 4 && reg < 13) {
		_8bitRegArray[reg] = data; // out of bounds probality
		return true;
	}
	return false;
}

bool _8086_Operations::mov16bitDataintoReg(int reg, uint16_t data) {
	if (reg > 0 && reg < 5) {
		_16bitRegArray[reg] = data;
		return true;
	}
	return false;
} // mov 16 bit into register

bool _8086_Operations::copyReg(int reg1, int reg2) { // reg 1  <- reg2
	if (reg1 == 0) { // this means we are moving data into ds reg
		Ds = static_cast<int>(_16bitRegArray[reg2]);

		return true;
	}
	if (reg1 < 5 && reg2 < 5) {
		uint16_t data = _16bitRegArray[reg2];
		return mov16bitDataintoReg(reg1, data);
	}
	if (reg1 > 4 && reg2 > 4) {
		uint8_t data = _8bitRegArray[reg2];
		return mov8bitDataintoReg(reg1, data);
	}
	return false;
}

uint16_t _8086_Operations::get16bitData(int reg) {
	if (reg >= 0 && reg <= 4) {
		return _16bitRegArray[reg];
	}
	return NULL;
}


uint8_t _8086_Operations::get8bitData(int reg) {
	if (reg >= 4 && reg <= 12) {
		return _8bitRegArray[reg];
	}
	return NULL;
}

uint8_t _8086_Operations::getDataFromMemory(int segment, int celladdress) {
	return mem->getData(segment, celladdress);
}
bool _8086_Operations::writeDataToMemory(int segment, int celladdress, uint8_t data) {
	if (mem->writeData(segment, celladdress, data)) {
		return true;
	}
	return false;
}
int _8086_Operations::getCellAddress(std::string data) {
	return std::stoi(data.substr(1, data.size() - 2));
}
std::vector<std::string> _8086_Operations::string_split_by_delimiter(std::string data, char delimiter) {

	std::stringstream stream(data);
	std::vector<std::string> splitdata;
	while (stream.good()) {
		std::string temp;
		std::getline(stream, temp, delimiter);
		splitdata.push_back(temp);
	}
	return splitdata;
}

uint8_t _8086_Operations::_8bitArithmeticOperations(int oprcode, int reg1, int reg2, bool isMemory, bool isData) {

	if (isData) { // immediate data
		if (oprcode == 2) return _8bitRegArray[reg1] + static_cast<uint8_t>(reg2);
		if (oprcode == 3) return _8bitRegArray[reg1] - static_cast<uint8_t>(reg2);
		if (oprcode == 4) return _8bitRegArray[reg1] * static_cast<uint8_t>(reg2);
	}
	if (isMemory) {// memory data
		uint8_t data = getDataFromMemory(Ds, reg2);
		if (oprcode == 2) return  _8bitRegArray[reg1] + data;
		if (oprcode == 3) return  _8bitRegArray[reg1] - data;
		if (oprcode == 4) return  _8bitRegArray[reg1] * data;


	}
	else { // both registers
		if (oprcode == 2) 	return  _8bitRegArray[reg1] + _8bitRegArray[reg2];
		if (oprcode == 3)	return  _8bitRegArray[reg1] - _8bitRegArray[reg2];
		if (oprcode == 4)	return  _8bitRegArray[reg1] * _8bitRegArray[reg2];

	}

}
uint16_t _8086_Operations::_16bitArithmeticOperations(int oprcode, int reg1, int reg2, bool isMemory, bool isData) {

	if (isData) {
		if (oprcode == 2) return _16bitRegArray[reg1] + static_cast<uint16_t>(reg2);
		if (oprcode == 3) return _16bitRegArray[reg1] - static_cast<uint16_t>(reg2);
		if (oprcode == 4) return _16bitRegArray[reg1] * static_cast<uint16_t>(reg2);
		if (oprcode == 5) {
			uint16_t dividend = _16bitRegArray[reg1];
			uint8_t divisor = static_cast<uint8_t>(reg2);
			uint8_t quotient = dividend / divisor;
			uint8_t remainder = dividend % divisor;
			std::string res = std::to_string(quotient) + std::to_string(remainder);
			int regpair = 5;
			if (reg1 == 1) regpair = 5;
			if (reg1 == 2) regpair = 7;
			if (reg1 == 3) regpair = 9;
			if (reg1 == 4) regpair = 11;
			_8bitRegArray[regpair] = quotient;
			_8bitRegArray[regpair + 1] = remainder;
			return static_cast<uint16_t>(std::stoi(res));
		}


	}
	if (isMemory) {
		std::string lower = std::to_string(getDataFromMemory(Ds, reg2));
		std::string higher = std::to_string(getDataFromMemory(Ds, reg2 + 1));
		lower += higher;
		uint16_t  data = std::stoi(lower);
		if (oprcode == 2) return  _16bitRegArray[reg1] + data;
		if (oprcode == 3) return  _16bitRegArray[reg1] - data;
		if (oprcode == 4) return  _16bitRegArray[reg1] * data;
		if (oprcode == 5) {
			uint16_t dividend = _16bitRegArray[reg1];
			uint8_t divisor = getDataFromMemory(Ds, reg2);
			uint8_t quotient = dividend / divisor;
			uint8_t remainder = dividend % divisor;
			std::string res = std::to_string(quotient) + std::to_string(remainder);
			int regpair = 5;
			if (reg1 == 1) regpair = 5;
			if (reg1 == 2) regpair = 7;
			if (reg1 == 3) regpair = 9;
			if (reg1 == 4) regpair = 11;
			_8bitRegArray[regpair] = quotient;
			_8bitRegArray[regpair + 1] = remainder;
			return static_cast<uint16_t>(std::stoi(res));
		}

	}
	else {
		if (oprcode == 2) return  _16bitRegArray[reg1] + _16bitRegArray[reg2];
		if (oprcode == 3) return  _16bitRegArray[reg1] - _16bitRegArray[reg2];
		if (oprcode == 4) return  _16bitRegArray[reg1] * _16bitRegArray[reg2];
		if (oprcode == 5) {
			uint16_t dividend = _16bitRegArray[reg1];
			uint8_t divisor = _8bitRegArray[reg2];
			uint8_t quotient = dividend / divisor;
			uint8_t remainder = dividend % divisor;
			std::string res = std::to_string(quotient) + std::to_string(remainder);
			int regpair = 5;
			if (reg1 == 1) regpair = 5;
			if (reg1 == 2) regpair = 7;
			if (reg1 == 3) regpair = 9;
			if (reg1 == 4) regpair = 11;
			_8bitRegArray[regpair] = quotient;
			_8bitRegArray[regpair + 1] = remainder;
			return static_cast<uint16_t>(std::stoi(res));
		}

	}

}

int _8086_Operations::registerPair(int reg1, int reg2) {
	if (reg1 < 5 && reg2 < 5) {
		return 11; // it means we have 16 bit  
	}
	else if (reg1 > 4 && reg2 > 4) {
		return 22; // it means we have 2 8 bit registers
	}
	else if (reg1 < 5 && reg2 > 4) { // it means we have 1 16bit register and 1 8bit register in
		return 12;					// in the order(16bit , 8bit ) 
	}
	else return 21; // (8 bit , 16bit)
}

bool _8086_Operations::executeCode(char* buffer) {
	int lines = mem->writeCodeBuffer(buffer);
	for (int i = 0; i < lines; i++) {
		int opcode = decoder->decodeAndGiveOperation(mem->getCode(i));
		performOperation(opcode, mem->getCode(i));
	}
	return true;
}
