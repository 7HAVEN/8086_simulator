#pragma once

#ifndef  __DECODER__
#define  __DECODER__
#include<string>
#include<vector>
class Decoder{
    public:    
        int decodeAndGiveOperation(std::vector<std::string> line);
        bool isRegister(std::string data);
        bool isMemory(std::string data);
        std::vector<std::string> string_split_by_delimiter(std::string data, char delimiter);
        int secondary_Operation(std::vector<std::string> parts);
};


#endif
