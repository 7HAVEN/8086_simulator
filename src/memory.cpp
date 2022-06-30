#include "./include/memory.h"

//std
#include<iterator>
#include<iostream>
#include<sstream>
memory::memory(int memoryCells) {
	this->memoryCells = memoryCells;
	MAX_LIMIT = 10000;
	memoryArray.resize(1000); // MAX limit is arbitarly set high to prevent memory outofbounds errors
	for (auto& i : memoryArray) {
		i.resize(MAX_LIMIT);
	}
	codeArray.resize(MAX_LIMIT); // same for code array
}
memory::~memory(){
	memoryArray.clear();
}

bool memory::writeData( int segment, int cellAddress, uint8_t data ) {
	try {
		auto x = memoryArray;
		memoryArray[segment][cellAddress] = data;
		return true;
	}
	catch (std::exception& e) {
		throw e;
	}
	return false;
}
uint8_t memory::getData(int segment, int cellAddress){
	if(cellAddress > MAX_LIMIT){
		throw "memory out of bounds";
	}
	else{
		return memoryArray[segment][cellAddress];
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
		codeArray[starting_address] = buf;
		
		return true;
	}
	catch (std::exception& e) {
		throw e;
	}
	return false;
}

std::vector<std::string> memory::getCode(int lineAddress) {
	return codeArray[lineAddress];
}

// bool memory::reset(int newSize) {
// 	//TODO make a popup
// 	std::string data;
// 	// memoryArray.set(memoryArray.start(), memoryArray.end(), data);

// 	memoryArray.clear(); // TODO { make a way that all the code doesn't fly away}
// 	return true;
// }

