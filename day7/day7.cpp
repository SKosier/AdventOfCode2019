/*
 * day7.cpp
 *
 *  Created on: Dec 8, 2019
 *      Author: sanja
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

std::vector<int> vec;
std::unordered_map<char, int> map;
std::map<int, std::pair<int, std::vector<int>>> amps;

int parse(int phase, int input) {
	bool first = true;
	std::vector<int> opcode(vec.begin(), vec.end());

	int i = 0, output = 0;
	while (opcode[i] != 99) {
		int opc = opcode[i] % 100;
		int mode_1 = (opcode[i] / 100) % 10;
		int mode_2 = (opcode[i] / 1000) % 10;
		int mode_3 = (opcode[i] / 10000) % 10;

		int a = mode_1 == 1 ? opcode[i + 1] : opcode[opcode[i + 1]];
		int b = mode_2 == 1 ? opcode[i + 2] : opcode[opcode[i + 2]];
		int c = opcode[i + 3];

		switch (opc) {
		case 1:
			opcode[c] = a + b;
			i += 4;
			break;
		case 2:
			opcode[c] = a * b;
			i += 4;
			break;
		case 3:
			opcode[opcode[i + 1]] = first ? phase : input;
			i += 2;
			first = false;
			break;
		case 4:
			output = opcode[opcode[i + 1]];
			i += 2;
			break;
		case 5:
			i = a != 0 ? b : i + 3;
			break;
		case 6:
			i = a == 0 ? b : i + 3;
			break;
		case 7:
			opcode[c] = a < b ? 1 : 0;
			i += 4;
			break;
		case 8:
			opcode[c] = a == b ? 1 : 0;
			i += 4;
			break;

		default:
			break;
		}
	}

	return output;
}

int parse_2part(bool first, int phase, int input, int amp_no) {
	std::vector<int>& opcode = amps[amp_no].second;
	int i = amps[amp_no].first;
	int output = 0;

	while (opcode[i] != 99) {
		int opc = opcode[i] % 100;
		int mode_1 = (opcode[i] / 100) % 10;
		int mode_2 = (opcode[i] / 1000) % 10;
		int mode_3 = (opcode[i] / 10000) % 10;

		int a = mode_1 == 1 ? opcode[i + 1] : opcode[opcode[i + 1]];
		int b = mode_2 == 1 ? opcode[i + 2] : opcode[opcode[i + 2]];
		int c = opcode[i + 3];

		switch (opc) {
		case 1:
			opcode[c] = a + b;
			i += 4;
			break;
		case 2:
			opcode[c] = a * b;
			i += 4;
			break;
		case 3:
			if(mode_1 == 1) opcode[i + 1] = first ? phase : input;
			else opcode[opcode[i + 1]] = first ? phase : input;
			i += 2;
			first = false;
			break;
		case 4:
			output = a;
			i += 2;
			amps[amp_no].first = i;
			return output;
		case 5:
			i = a != 0 ? b : i + 3;
			break;
		case 6:
			i = a == 0 ? b : i + 3;
			break;
		case 7:
			opcode[c] = a < b ? 1 : 0;
			i += 4;
			break;
		case 8:
			opcode[c] = a == b ? 1 : 0;
			i += 4;
			break;

		default:
			break;
		}
	}
	throw std::runtime_error{ "Opcode 99" };
}


int main() {
	int n;
	char c;

	while (std::cin >> n) {
		vec.push_back(n);
		std::cin >> c;
	}

	int ints[5] = { 0, 1, 2, 3, 4 };
	std::vector<int> outputs;
	do {
		outputs.push_back(
				parse(ints[4],
						parse(ints[3],
								parse(ints[2],
										parse(ints[1], parse(ints[0], 0))))));
	} while (std::next_permutation(ints, ints + 5));
	int max = *std::max_element(outputs.begin(), outputs.end());
	std::cout << "First part: " << max << std::endl;


	int ints_2[5] = { 5, 6, 7, 8, 9 };
	std::vector<int> outputs_2;

	do {
		int input = 0;
		bool first[5] = {true, true, true, true, true};
		for(int i = 0; i < 5; i++) amps[i] = {0, vec};

		try {
			while(true) {
				for(int i = 0; i < 5; i++) {
					input = parse_2part(first[i], ints_2[i], input, i);
					first[i] = false;
				}
			}
		} catch (std::runtime_error& error) {
			outputs_2.push_back(input);
		}

	} while (std::next_permutation(ints_2, ints_2 + 5));

	max = *std::max_element(outputs_2.begin(), outputs_2.end());
	std::cout << "Second part: " << max << std::endl;

}
