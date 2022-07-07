#pragma once

#ifndef _Operations_
#define _Operations_

#include "memory.h" // user def

//std
#include<string>
#include<vector>
#include<sstream>

class _8086_Operations {
public:
	_8086_Operations(memory *m);
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
	uint8_t arithmeticOperations(int opcode,int reg1 , int reg2 , bool isMemory = false);
	int registerPair(int reg1 , int reg2);
private:
	memory *mem;

	int programCounter;
	int Ds; // ds reg 0
	//uint16_t Ax; // 1 
	//uint16_t Bx; // 2
	//uint16_t Cx;//  3
	//uint16_t Dx; // 4

	uint16_t _16bitRegArray[5];

	//8bit counterparts
	//uint8_t Ah;//4
	//uint8_t Al;//5

	//uint8_t Bh;//6
	//uint8_t Bl;//7

	//uint8_t Ch;//8
	//uint8_t Cl;//9

	//uint8_t Dh;//10
	//uint8_t Dl;//11

	uint8_t _8bitRegArray[8];




};




#endif