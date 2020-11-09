//
// Created by alfredd on 11/8/20.
//
#include <iostream>
#include <fstream>
#include <cstdlib>

int main(int argc, char **argv)
{
	std::ofstream file;
	file.open("testfile.dat", std::ios::in | std::ios::out);
	file << "Test data" << std::endl;
	file.close();

	auto envVar = std::getenv("MYVAR");
	if (envVar)
		std::cout << "Environment variable is: '" << envVar << "'" << std::endl;

	std::string line;
	std::ifstream ifile;

	ifile.open("testfile.dat", std::ios::in | std::ios::out);
	if (ifile.is_open()) {
		while(std::getline(ifile, line)) {
			std::cout<< line<< std::endl;
		}
	}
	ifile.close();
}