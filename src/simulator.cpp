#include  "include/window.h"
#include "include/memory.h"
#include "include/decoder.h"
#include "include/operations.h"
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
		 m.writeCode(0, "MOV Ax,0020");
		 m.writeCode(1, "MOV Ds,Ax");
		 m.writeCode(2, "MOV Ah,30");
		 m.writeCode(3, "MOV Al,40");
		 //m.writeCode(4, "ADD 34,ch");// error (Exception test) // may want to make a custom exception in future
		
		 Decoder d;
		 _8086_Operations  oper(&m);
		 int opcode = d.decodeAndGiveOperation(m.getCode(0));
		
		 oper.performOperation(opcode, m.getCode(0));
		 opcode = d.decodeAndGiveOperation(m.getCode(1));
		 oper.performOperation(opcode, m.getCode(1));
		 
		 opcode = d.decodeAndGiveOperation(m.getCode(4));
		 std::cout << opcode;

		

		 
		
	 }
	 
	 catch(std::exception &e) {
	 	std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	 }

	
	
	return EXIT_SUCCESS;
}

