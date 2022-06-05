#pragma once

#ifndef _memory_
#define _memory_
//std
#include<string>
#include<vector>
#include<utility>

class memory {
private:
	int memoryCells;
	std::vector<uint8_t> memoryArray; // memory array is diffrent from code array as it will only store intgers in it
	std::vector<std::pair<int,std::vector<std::string>>> codeArray; 
	int MAX_LIMIT;
public:
	memory(int memoryCells);
	~memory();
	uint8_t getData(int cellAddress);
	std::vector<std::string> string_splitter(std::string data);
	bool writeData(uint8_t data, int cellAddress);
	bool reset(int newSize);
	bool writeCode(int starting_address , std::string codeLines);
};

#endif