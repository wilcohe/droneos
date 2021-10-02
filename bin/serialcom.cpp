#include <string.h>
#include <iostream>
#include <cstdlib>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(){
	const char* ard_prt;
	if (const char* port_test = std::getenv("ARDUINO_PORT")){
		ard_prt = std::getenv("ARDUINO_PORT");
		}
	else{
		std::cout << "There is no Arduino port recognized" << "\n";
		return 1;
	}
	int fd;

	if ((fd=serialOpen( ard_prt, 115200))<0){
		std::cout << "Unable to open serial connection" << "\n";
		return 1;
	}

	for (;;){
		putchar(serialGetchar(fd)); 
		fflush(stdout);
	}
}

