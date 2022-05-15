#include  "include/window.h"


//std
#include<string>
#include<vector>
#include<iostream>

int main(int argv, char argc[]) {
	try {
		window w = window(1280, 720, "Example");
		
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
		
	}
	
	
	return EXIT_SUCCESS;
}

