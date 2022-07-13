#pragma once

#ifndef _memory_
#define _memory_
//std
#include<string>
#include<vector>

class memory {
private:
	int memoryCells;
	int MAX_LIMIT;
	std::vector<std::vector<std::string>> codeArray; // code array
	std::vector <std::vector<uint8_t>>memoryArray; // memory array is diffrent from code array as it will only store intgers in it
public:
	memory(int memoryCells);
	~memory();
	uint8_t getData(int segment,int cellAddress);
	bool writeData(int segment,int cellAddress, uint8_t data);

	std::vector<std::string> getCode(int lineAddress);
	std::vector<std::string> string_splitter(std::string data);
	bool reset(int newSize);
	int writeCodeBuffer(char* buffer);
	bool writeCode(int starting_address , std::string codeLines);
};

#endif