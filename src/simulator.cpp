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
		 m.writeCode(2, "MOV [0001],Ah");
		 m.writeCode(3, "MOV Al,Ah");
		 m.writeCode(4, "MOV Al,[0002]");
		
		 Decoder d;
		 _8086_Operations  oper(&m);
		 int opcode = d.decodeAndGiveOperation(m.getCode(0));
		
		 oper.performOperation(opcode, m.getCode(0));
		 opcode = d.decodeAndGiveOperation(m.getCode(1));
		 oper.performOperation(opcode, m.getCode(1));

		 m.writeData(20, 1, 43);

		 std::cout << (unsigned)m.getData(20, 1) << "\n";
		 opcode = d.decodeAndGiveOperation(m.getCode(2));
		 oper.performOperation(opcode, m.getCode(2));
		 oper.mov8bitDataintoReg(5, 23);
		 std::cout << (unsigned)oper.get8bitData(5) << "\n";
		 std::vector<std::string> t = m.getCode(3);
		 opcode = d.decodeAndGiveOperation(m.getCode(3));
		 oper.performOperation(opcode, m.getCode(3));
		 std::cout << (unsigned)oper.get8bitData(6) << "\n";
		 opcode = d.decodeAndGiveOperation(m.getCode(4));
		 oper.performOperation(opcode, m.getCode(4));
		 std::cout << (unsigned)m.getData(20, 2) << "\n";
		 
	


		 
		
	 }
	 catch(std::exception &e) {
	 	std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	 }
	
	
	return EXIT_SUCCESS;
}

