#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "serialcom.h"

std::string get_data(int fd){
	serialFlush(fd);
	char b;
	std::string pose;
	while(serialGetchar(fd) != '\n');
	do{
		b = serialGetchar(fd);
		pose += b;
	}while (b != '\n');

	return pose;
}

std::vector<float> parse_data(std::string& pose){
	std::vector<float> pose_vec;
	std::string xyz = "";
	for (std::string::iterator it=pose.begin(); it < pose.end(); ++it){
		if (*it == ',' || *it == '\n'){
			pose_vec.push_back(std::stof(xyz));
			std::string xyz = ""; 
		}
	}
	return pose_vec;
}


int connect(){

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

	return fd;
}

