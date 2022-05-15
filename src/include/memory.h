#pragma once

#ifndef _memory_
#define _memory_
//std
#include<string>
#include<vector>

class memory {
private:
	int memoryCells;
	std::vector<std::string> memoryArray;
	int MAX_LIMIT;
public:
	memory(int memoryCells);
	~memory();
	std::string getData(int cellAddress);
	bool writeData(std::string data, int cellAddress);
	bool reset(int newSize);
};

#endif