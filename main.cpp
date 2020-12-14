//
// Created by Vladan Kudlac (kudlav) on 14.12.2020.
//

#include <iostream>
#include <cctype> // isalnum


#include "Encoder.h"

#define EXIT_ARG 1 // error when parsing arguments

void reversePrint(std::string str) {
	for (int i = str.length(); i >= 0; --i)
		std::cout << str[i];
}

void printHelp() {
	std::cerr << "Usage:" << std::endl;
	std::cerr << " - encode:   ./bms -e <<< [ASCII string]" << std::endl;
	std::cerr << " - decode:   ./bms -d <<< [string containing 0/1 characters]" << std::endl;
}

void decode() {

}

void encode() {
	Encoder encoder;
	std::string input;
	std::string output;

	// Read input
	std::string line;
	while(std::getline(std::cin, line)) {
		input += line;
	}

	// Encode characters
	for(unsigned long i = input.size(); i-- > 0; ) {
		char c = input[i];
		if (isalnum(c)) output += encoder.step(8, c);
	}

	// Flush shift register
	output += encoder.step(5, 0);

	reversePrint(output);
}

int main(int argc, char* argv[]) {

	if (argc == 2 && strcmp(argv[1], "-d") == 0) {
		decode();
	}
	else if (argc == 2 && strcmp(argv[1], "-e") == 0) {
		encode();
	}
	else {
		printHelp();
		exit(EXIT_ARG);
	}

	return EXIT_SUCCESS;
}

