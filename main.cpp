//
// Created by Vladan Kudlac (kudlav) on 14.12.2020.
//

#include <iostream>
#include <cctype> // isalnum
#include <cstring> // strcmp

#include "Encoder.h"
#include "Decoder.h"

#define EXIT_ARG 1 // error when parsing arguments


void reversePrint(std::string str) {
	for (int i = str.length(); i >= 0; --i)
		std::cout << str[i];
	std::cout << std::endl;
}

void printHelp() {
	std::cerr << "Usage:" << std::endl;
	std::cerr << " - encode:   ./bms -e <<< [ASCII string]" << std::endl;
	std::cerr << " - decode:   ./bms -d <<< [string containing 0/1 characters]" << std::endl;
}

void decode(std::string input) {
	Decoder decoder;
	unsigned char inputBits[2];
	unsigned char inputIndex = 0;

	for(unsigned long i = input.size(); i-- > 0; ) {
		char c = input[i];

		if (c == '0' || c == '1')
			inputBits[inputIndex++] = c;

		if (inputIndex == 2) {
			decoder.step(inputBits);
			inputIndex = 0;
		}
	}

	decoder.result();

}

void encode(std::string input) {
	Encoder encoder;
	std::string output;

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

	std::string input;

	// Read input
	std::string line;
	while(std::getline(std::cin, line)) {
		input += line;
	}

	if (argc == 2 && strcmp(argv[1], "-d") == 0) {
		decode(input);
	}
	else if (argc == 2 && strcmp(argv[1], "-e") == 0) {
		encode(input);
	}
	else {
		printHelp();
		exit(EXIT_ARG);
	}

	return EXIT_SUCCESS;
}

