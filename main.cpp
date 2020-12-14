//
// Created by Vladan Kudlac (kudlav) on 14.12.2020.
//

#include <iostream>
#include <cctype> // isalnum

#include "Encoder.h"


void print(std::string str) {
	for (int i = str.length(); i >= 0; --i)
		std::cout << str[i];
}

int main() {

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
		if (!isalnum(c))
			continue;

		output += encoder.step(8, c);
	}
	output += encoder.step(5, 0);

	print(output);

	return EXIT_SUCCESS;
}

