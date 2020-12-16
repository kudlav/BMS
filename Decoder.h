//
// Created by Vladan Kudlac (kudlav) on 14.12.2020.
//

#ifndef PROJEKTBMS_DECODER_H
#define PROJEKTBMS_DECODER_H

#include <vector> // vector
#include <limits> // numeric_limits

class Decoder {

	const unsigned int DROP_CHARS = 5;
	std::vector<unsigned char> paths[32];
	unsigned int costs[32];

public:
	Decoder() {
		for (unsigned char i = 0; i < sizeof(costs)/sizeof(costs[0]); i++) {
			costs[i] = 0;
		}
	}

	/* Calculate n+1 states */
	void step(unsigned char input[]) {
		unsigned int costsN1[32];
		unsigned char prevA;
		unsigned char prevB;
		unsigned int costA;
		unsigned int costB;

		// Calculate n+1 state costs
		for (unsigned char stateN1 = 0; stateN1 < sizeof(costs)/sizeof(costs[0]); stateN1++) {
			prevA = (stateN1 << 1) & 31;	// dropped value was 0
			prevB = prevA | 1;				// dropped value was 1
			costA = costs[prevA] + distance(input, prevA, stateN1);
			costB = costs[prevB] + distance(input, prevB, stateN1);
			if (costA <= costB) {
				costsN1[stateN1] = costA;
				paths[stateN1].push_back(prevA);
			} else {
				costsN1[stateN1] = costB;
				paths[stateN1].push_back(prevB);
			}
		}

		// Update costs from N+1 step into N step
		for (unsigned char i = 0; i < sizeof(costs)/sizeof(costs[0]); i++) {
			costs[i] = costsN1[i];
		}
	}

	void result() {
		// Find final lowest cost
		unsigned char backtrackState = 0;
		unsigned char lowestCost = costs[0];
		for (unsigned char i = 1; i < sizeof(costs)/sizeof(costs[0]); i++) {
			if (costs[i] < lowestCost) {
				backtrackState = i;
				lowestCost = costs[i];
			}
		}

		// Traverse final path (drop segment to n=0)
		unsigned int dropChars = DROP_CHARS;
		unsigned char letter = 0;
		unsigned char nBits = 0;
		for (size_t i = paths->size(); i-- > 0; ) {
			if (dropChars == 0) {
				nBits++;
				letter <<= 1;
				if ((backtrackState & 16) == 16) {
					letter += 1; // highest n+1 bit means input of n step
				}
				if (nBits == 8) {
					std::cout << letter;
					nBits = 0;
					letter = 0;
				}
			} else {
				dropChars--;
			}
			backtrackState = paths[backtrackState][i];
		}
	}

private:
	static unsigned int distance(const unsigned char a[], unsigned short stateN, unsigned short stateN1) {
		// Recreate memory in N step with input from n+1 step
		uint8_t mem = stateN1 << 1;
		mem |= stateN;

		// Get generator output
		std::string b = Encoder::outputBits(mem);

		// Compute distance
		unsigned int distance = 0;
		if (a[0] != b[0]) distance++;
		if (a[1] != b[1]) distance++;
		return distance;
	}

};


#endif //PROJEKTBMS_DECODER_H
