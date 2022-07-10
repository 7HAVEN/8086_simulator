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
		 m.writeCode(2, "DIV bx,[5]");// done
		 m.writeCode(3, "add ah,7");// done

		
		 //m.writeCode(4, "ADD 34,ch");// error (Exception test) // may want to make a custom exception in future
		
		 Decoder d;
		 _8086_Operations  oper(&m);
		 int opcode = d.decodeAndGiveOperation(m.getCode(0));
		
		 oper.performOperation(opcode, m.getCode(0));
		 opcode = d.decodeAndGiveOperation(m.getCode(1));
		 oper.performOperation(opcode, m.getCode(1));
		 oper.mov8bitDataintoReg(5, 10);
		 oper.mov16bitDataintoReg(2, 23);
		

		 m.writeData(20, 5, 5);
	     //m.writeData(20, 46, 5);
		 int line = 2;
		 opcode = d.decodeAndGiveOperation(m.getCode(line ));
		 
		 oper.performOperation(opcode, m.getCode(line));
		 std::cout << (unsigned)oper.get8bitData(7) << std::endl;
		 std::cout << (unsigned)oper.get8bitData(8);

		 //std::cout << (unsigned)oper.get16bitData(1);

		 //std::cout << opcode;

		

		 
		
	 }
	 
	 catch(std::exception &e) {
	 	std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	 }

	
	
	return EXIT_SUCCESS;
}

