/*
 * day5.cpp
 *
 *  Created on: Dec 5, 2019
 *      Author: sanja
 */

#include <iostream>
#include <vector>

std::vector<int> vec;

int parse(int input) {
	std::vector<int> opcode(vec.begin(), vec.end());

	int i = 0;
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
			opcode[opcode[i + 1]] = input;
			i += 2;
			break;
		case 4:
			std::cout << opcode[opcode[i + 1]] << std::endl;
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
}

int main() {
	int n, input;
	char c;
	std::cout << "Input ID: ";
	std::cin >> input;
	while (std::cin >> n) {
		vec.push_back(n);
		std::cin >> c;
	}

	parse(input);
}

