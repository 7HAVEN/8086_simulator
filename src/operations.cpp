#include "include/operations.h"
#include<memory>
_8086_Operations::_8086_Operations(memory *m) :mem(m){
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
	if (Opcode == 112) { // reg to mem mov
		int reg1 = whichReg(parts[0]);
		uint8_t data = _8bitRegArray[reg1];
		int celladdr = getCellAddress(parts[1]);
		writeDataToMemory(Ds, celladdr, data);
		return true;
		 
	}
	if (Opcode == 121) { // mem to reg
		int reg1 = whichReg(parts[1]);
		int addr = getCellAddress(parts[0]);
		uint8_t  data = getDataFromMemory(Ds, addr);
		mov8bitDataintoReg(reg1, data);
		return true;
	}
	if (Opcode == 113) { // immediate data to reg
		int reg1 = whichReg(parts[0]);
		uint16_t intData = std::stoi(parts[1]);
	/*	uint8_t  data = static_cast<uint8_t>(intData);*/
		
		
		_16bitRegArray[reg1] = intData;
		return true;
	}

	if (Opcode == 211) {
		
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

	if (reg > 4 && reg < 12) {
		_8bitRegArray[reg] = data; // out of bounds probality
		return true;
	}
	return false;
}

bool _8086_Operations::mov16bitDataintoReg(int reg, uint16_t data) {
	if (reg > 0 && reg < 4) {
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
	if (reg1 < 4 && reg2 < 4) {
		uint16_t data = _16bitRegArray[reg2];
		return mov16bitDataintoReg(reg1, data);
	}
	if (reg1 > 3 && reg2 > 3) {
		uint8_t data = _8bitRegArray[reg2];
		return mov8bitDataintoReg(reg1, data);
	}
	return false;
}

uint16_t _8086_Operations::get16bitData(int reg) {
	if (reg >= 0 && reg <= 3) {
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
bool _8086_Operations::writeDataToMemory(int segment, int celladdress,uint8_t data) {
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

uint8_t _8086_Operations::arithmeticOperations(int opercode,int reg1 , int reg2 , bool isMemory = false) {
	if (opercode == 11) {
		
		if(registerPair(reg1, reg2) == 11){}
	}
}

int _8086_Operations::registerPair(int reg1 , int reg2) {
	if (reg1 < 4 && reg2 < 4) {
		return 11; // it means we have 16 bit registers
	}
	else if (reg1 > 3 && reg2 > 3) {
		return 22; // it means we have 2 8 bit registers
	}
	else if (reg1 > 3 && reg2 < 4) { // it means we have 1 16bit register and 1 8bit register in
		return 21;					// in the order(16bit , 8bit ) 
	}
	else return 12; // (8 bit , 16bit)
}
