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
		 window w = window(1280, 800, "simulator",&d,&oper);
		 
		 char *buf =  "mov ah,20\nmov bh,40\nadd ah,bh"; 
		 oper.executeCode(buf);
		

		

		 
		
	 }
	 
	 catch(std::exception &e) {
	 	std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	 }

	
	
	return EXIT_SUCCESS;
}

