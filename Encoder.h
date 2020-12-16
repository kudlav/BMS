//
// Created by Vladan Kudlac (kudlav) on 14.12.2020.
//

#ifndef PROJEKTBMS_ENCODER_H
#define PROJEKTBMS_ENCODER_H

#include <cctype> // isalnum

class Encoder {

	uint8_t memory = 0;

public:
	std::string step(unsigned int nSteps, unsigned char input) {
		std::string out;
		for (unsigned int i = 0; i < nSteps; i++) {
			// Set lowest input bit to highest bit in register
			uint8_t inputLob = (input & 1);
			memory |= (inputLob << 5);

			out += outputBits(memory);

			// Shift the register and input
			memory >>= 1;
			input >>= 1;
		}
		return out;
	}

	static std::string outputBits(uint8_t mem) {
		std::string out = "xx";

		// XOR output - low order bit
		if (((mem & 2) != 0) != ((mem & 4) != 0) != ((mem & 8) != 0) != ((mem & 32) != 0))
			out[0] = '1';
		else
			out[0] = '0';

		// XOR output - high order bit
		if (((mem & 1) != 0) != ((mem & 4) != 0) != ((mem & 16) != 0) != ((mem & 32) != 0))
			out[1] = '1';
		else
			out[1] = '0';

		return out;
	}

};

#endif //PROJEKTBMS_ENCODER_H
