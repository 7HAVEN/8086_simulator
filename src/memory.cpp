#include "../include/memory.h"

memory::memory(int memoryCells) {
	this->memoryCells = memoryCells;
	MAX_LIMIT = 10000;
	
	memoryArray.resize(MAX_LIMIT); // MAX limit is arbitarly set high to prevent memory outofbounds errors
	
}

bool memory::writeData(std::string data, int cellAddress) {
	try {
		memoryArray[cellAddress] = data;
		return true;
	}
	catch (std::exception& e) {
		throw e;
	}
	return false;
}

bool memory::reset(int newSize) {
	//TODO make a popup
	memoryArray.clear(); // TODO { make a way that all the code doesn't fly away}
	return true;
}

