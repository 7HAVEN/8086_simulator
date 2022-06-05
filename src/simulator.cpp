#include  "include/window.h"
 #include "include/memory.h"
 #include "include/decoder.h"

//std
#include<string>
#include<vector>
#include<iostream>

int main(int argv, char argc[]) {
	 try {
		
		//window w = window(1280, 720, "Example");
		 memory m = memory(3000);
		 /*m.writeData("MOV A,B",0001);
		std::string data = m.getData(0002);
		std::cout << data;*/
		 m.writeCode(0, "MOV A,B");
		 m.writeCode(1, "MOV C,X");
		 

		// std::cout <<  decode.decodeAndGiveOperation("MOV");


		
		
	 }
	 catch(std::exception &e) {
	 	std::cout << e.what() << std::endl;
		
	 }
	
	
	return EXIT_SUCCESS;
}

