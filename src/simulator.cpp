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
		
		
		 memory m = memory(3000);
		 Decoder d;
		 _8086_Operations  oper(&m,&d);
		 m.writeData(34, 0, 43);
		 oper.mov16bitDataintoReg(1, 43);
		 window w = window(1280, 720, "simulator",&d,&oper);
		 /*m.writeData("MOV A,B",0001);
		std::string data = m.getData(0002);
		std::cout << data;*/
		 m.writeCode(0, "MOV Ax,0020");
		 m.writeCode(1, "MOV Ds,Ax");
		 m.writeCode(2, "DIV bx,ah");// done
		 m.writeCode(3, "add ah,7");// done

		 char* buf = "mov ax,0020\nmov ds,ax\nmov ah,8\nmov al,4\n add ah,al";
		 oper.executeCode(buf);
		 std::cout << (unsigned)oper.get8bitData(5);
			
		 //std::cout << opcode;

		

		 
		
	 }
	 
	 catch(std::exception &e) {
	 	std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	 }

	
	
	return EXIT_SUCCESS;
}

