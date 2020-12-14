//
// Created by Vladan Kudlac (kudlav) on 14.12.2020.
//

#ifndef PROJEKTBMS_ENCODER_H
#define PROJEKTBMS_ENCODER_H

#include <sstream> // ostringstream


class Encoder {

private:
	uint8_t memory = 0;

public:
	std::string step(int nSteps, unsigned char input) {
		std::ostringstream out;
		for (int i = 0; i < nSteps; i++) {
			// Set lowest input bit to highest bit in register
			uint8_t inputLob = (input & 1);
			memory |= (inputLob << 5);

			// XOR output - low order bit
			if (((memory & 2) != 0) != ((memory & 4) != 0) != ((memory & 8) != 0) != ((memory & 32) != 0))
				out << '1';
			else
				out << '0';

			// XOR output - high order bit
			if (((memory & 1) != 0) != ((memory & 4) != 0) != ((memory & 16) != 0) != ((memory & 32) != 0))
				out << '1';
			else
				out << '0';

			// Shift the register and input
			memory >>= 1;
			input >>= 1;
		}
		return out.str();
	}

};

#endif //PROJEKTBMS_ENCODER_H
