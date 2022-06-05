#include "./include/memory.h"

//std
#include<iterator>
#include<iostream>
#include<sstream>
memory::memory(int memoryCells) {
	this->memoryCells = memoryCells;
	MAX_LIMIT = 10000;
	memoryArray.resize(MAX_LIMIT,(uint8_t)0); // MAX limit is arbitarly set high to prevent memory outofbounds errors
}
memory::~memory(){
	memoryArray.clear();
}

bool memory::writeData(uint8_t data, int cellAddress) {
	try {

		memoryArray[cellAddress] = data;
		return true;
	}
	catch (std::exception& e) {
		throw e;
	}
	return false;
}
uint8_t memory::getData(int cellAddress){
	if(cellAddress > MAX_LIMIT){
		throw "memory out of bounds";
	}
	else{
		return memoryArray[cellAddress];
	}
}

std::vector<std::string> memory::string_splitter(std::string data){
	std::stringstream buffer(data);
	std::string temp;
	std::vector<std::string> split_array;
	while (buffer >> temp) {
		split_array.push_back(temp); 
	}

	return split_array;
}


bool memory::writeCode(int starting_address, std::string codeLines) {
	try {

		std::vector<std::string> buf = string_splitter(codeLines);
		codeArray.push_back({ starting_address,buf });
		
		return true;
	}
	catch (std::exception& e) {
		throw e;
	}
	return false;
}

// bool memory::reset(int newSize) {
// 	//TODO make a popup
// 	std::string data;
// 	// memoryArray.set(memoryArray.start(), memoryArray.end(), data);

// 	memoryArray.clear(); // TODO { make a way that all the code doesn't fly away}
// 	return true;
// }

