#include "./include/decoder.h"


// std
#include<sstream>

int Decoder::decodeAndGiveOperation(std::vector<std::string> line) {
    try {

        std::string  data = line[0];

        //!(warn) this line will cause out of bounds error for one word instructions
        std::string secondHalfofInstruction = line[1]; // the second half of string
        std::vector<std::string> parts = string_split_by_delimiter(secondHalfofInstruction, ',');
        //1
        if (data == "MOV" || data == "mov") {
            if (isRegister(parts[0])) { // first agrument is register 
                if (isRegister(parts[1])) { // second arg is reg
                    return 111; //1 mov 1 reg 1 reg
                }
                if (isMemory(parts[1])) { // second arg is mem
                    return 112; //1 mov 1 reg 2 mem
                }

                else { //1 mov 1 reg 3 immediate data
                    return 113;
                }
            }
            else { // first part is mem
                if (isRegister(parts[1])) { // second arg is reg
                    return 121;
                }
                else { // second arg is mem as mem to mem data transfer is not possible ;-(
                    throw "invalid operation";
                }
            }

        }
        //2    
        else if (data == "ADD" || data == "add") {
            int opcodeRange = 200;
            int operation_code = secondaryOperation(parts);
            return opcodeRange + operation_code;
        }
        else if (data == "SUB" || data == "sub") {
            int opcodeRange = 300;
            int operation_code = secondaryOperation(parts);
            return opcodeRange + operation_code;
        }
        else if (data == "MUL" || data == "mul") {
            int opcodeRange = 400;
            int operation_code = secondaryOperation(parts);
            return opcodeRange + operation_code;
        }
        else if (data == "DIV" || data == "div") {
            int opcodeRange = 500;
            int operation_code = secondaryOperation(parts);
            return opcodeRange + operation_code;
        }
            
    }

    catch (std::exception e) {
        throw e;
    }
        
    return 0;

}

bool Decoder::isRegister(std::string data) {
    //16 bit register
    if (data == "AX" || data == "Ax" || data == "ax") {
        return true;
    }
    if (data == "BX" || data ==  "Bx" || data == "bx") {
        return true;
    }
    if (data == "CX" || data == "Cx" || data == "cx") {
        return true;
    }
    if (data == "DX" || data == "Dx" || data == "dx") {
        return true;
    }
    if (data == "DS" || data == "Ds" || data == "ds") {
        return true;
    }
    //8bit registers

    if (data == "AH" || data == "Ah" || data == "ah") {
        return true;
    }
    if (data == "AL" || data == "Al" || data == "al") {
        return true;
    }

    if (data == "BH" || data == "Bh" || data == "bh") {
        return true;
    }
    if (data == "BL" || data == "Bl" || data == "bl") {
        return true;
    }

    if (data == "CH" || data == "Ch" || data == "ch") {
        return true;
    }
    if (data == "CL" || data == "Cl" || data == "cl") {
        return true;
    }

    if (data == "DH" || data == "Dh" || data == "dh") {
        return true;
    }
    if (data == "DL" || data == "Dl" || data == "dl") {
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



std::vector<std::string> Decoder::string_split_by_delimiter(std::string data, char delimiter) {

    std::stringstream stream(data);
    std::vector<std::string> splitdata;
    while (stream.good()) {
        std::string temp;
        std::getline(stream, temp, delimiter);
        splitdata.push_back(temp);
    }
    return splitdata;
}

int Decoder::secondaryOperation(std::vector<std::string> parts) {
    
    if (isRegister(parts[0])) {
        if (isRegister(parts[1]))
            return 11; // register to register operation ( ax + bx)
        if (isMemory(parts[1]))
            return 12; // register with  memory 
        else
            return 13;// register with immediate data
    }
    if (isMemory(parts[0])) {
        if (isRegister(parts[1]))
            return 21;

    }
    else {
        throw "invalid operation";
        return -1;
    }
   
}
