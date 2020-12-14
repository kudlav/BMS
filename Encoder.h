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
	std::string step(int nSteps, char input) {
		std::ostringstream out;
		for (int i = 0; i < nSteps; i++) {
			uint8_t inputLob = (input & 1);
			memory |= (inputLob << 5);

			// outLob
			if (((memory & 2) != 0) != ((memory & 4) != 0) != ((memory & 8) != 0) != ((memory & 32) != 0))
				out << '1';
			else
				out << '0';

			// outHob
			if (((memory & 1) != 0) != ((memory & 4) != 0) != ((memory & 16) != 0) != ((memory & 32) != 0))
				out << '1';
			else
				out << '0';

			memory >>= 1;
			input >>= 1;
		}
		return out.str();
	}

	void reset() {
		memory = 0;
	}

};


#endif //PROJEKTBMS_ENCODER_H
