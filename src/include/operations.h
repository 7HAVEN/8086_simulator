#pragma once

#ifndef _Operations_
#define _Operations_

#include "memory.h" // user def
#include "decoder.h"
//std
#include<string>
#include<vector>
#include<sstream>

class _8086_Operations {
public:
	_8086_Operations(memory *m ,Decoder *d);
	_8086_Operations();
	bool performOperation(int Opcode, std::vector<std::string> line);
	bool mov8bitDataintoReg(int reg, uint8_t data); // mov 8 bit into register
	bool mov16bitDataintoReg(int reg, uint16_t data); // mov 16 bit into register
	bool copyReg(int reg1, int reg2); // reg2 <- reg1
	uint16_t get16bitData(int reg);
	uint8_t get8bitData(int reg);
	uint8_t getDataFromMemory(int segment,int celladdress); //!potential memory leaks
	int getCellAddress(std::string data);
	int whichReg(std::string data);
	bool writeDataToMemory(int segment, int celladdress,uint8_t data);
	std::vector<std::string> string_split_by_delimiter(std::string data, char delimiter);
	uint8_t _8bitArithmeticOperations(int oprcode,int reg1 , int reg2 , bool isMemory ,bool isData);
	uint16_t _16bitArithmeticOperations(int oprcode, int reg1, int reg2, bool isMemory, bool isData);
	bool executeCode(char *buffer);
	int registerPair(int reg1 , int reg2);
	
	uint16_t _16bitRegArray[5];

	uint8_t _8bitRegArray[13];
	int Ds; // ds reg 0


private:
	memory *mem;
	Decoder* decoder;

	int programCounter;



};




#endif