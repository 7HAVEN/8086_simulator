#include "./include/decoder.h"


// std
#include<sstream>

int Decoder::decodeAndGiveOperation(std::vector<std::string> line){
    
    std::string  data = line[0];
   //!(warn) this line will cause out of bounds error for one line instructions

    std::string secondHalfofInstruction = line[1]; // the second half of string
    std::vector<std::string> parts  = string_split_by_delimiter(secondHalfofInstruction, ',');
    if (data == "MOV" || data == "mov") {
        if (isRegister(parts[0])) { // first agrument is register 
            if (isRegister(parts[1])) { // second arg is reg
               
            }
            else { // second arg is mem
               
            }
        }
        else { // first part is mem
            if (isRegister(parts[1])) { // second arg is reg

            }
            else { // second arg is mem as mem to mem data transfer is not possible ;-(
                throw "invalid operation";
            }
        }
        
    }
        
    else if (data == "ADD" || data == "add")
        return 2;
    else if (data == "SUB" || data == "sub")
        return 3;
        
    return 0;

}

bool Decoder::isRegister(std::string data) {
    if (data == "AX" || data == "Ax" || data == "ax") {
        return true;
    }
    if (data == "BX" || data == "Bx" || data == "bx") {
        return true;
    }
    if (data == "BX" || data == "Bx" || data == "bx") {
        return true;
    }
    if (data == "CX" || data == "Cx" || data == "cx") {
        return true;
    }
    return false;
    
}
bool Decoder::isMemory(std::string data) {
    if (data[0] == '[') {
        return true;
    }
    return false;
}



std::vector<std::string> string_split_by_delimiter(std::string data, char delimiter) {

    std::stringstream stream(data);
    std::vector<std::string> splitdata;
    while (stream.good()) {
        std::string temp;
        std::getline(stream, temp, delimiter);
        splitdata.push_back(temp);
    }
    return splitdata;
}


