/*
 * day11.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: sanja
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <fstream>

std::map<std::pair<int, int>, int> map;

void moveForward(std::pair<int, int>& pos, int& angle) {
	if(angle == 360) angle -=360;
	else if(angle < 0) angle += 360;
	if(angle == 0) pos.second++;
	if(angle == 180) pos.second--;
	if(angle == 90) pos.first++;
	if(angle == 270) pos.first--;
}

long long int parse(long long int input, std::vector<long long int>& opcode) {

	bool isFirst = true;
	int angle = 0;
	long long int i = 0, relative_base = 0;
	std::pair<int, int> pos = std::make_pair(0, 0);
	while (opcode[i] != 99) {
		int opc = opcode[i] % 100;
		int mode_1 = (opcode[i] / 100) % 10;
		int mode_2 = (opcode[i] / 1000) % 10;
		int mode_3 = (opcode[i] / 10000) % 10;

		long long int a, b, c;

		if(mode_1 == 2) a = (long long int) opcode[relative_base + opcode[i + 1]];
		else a = mode_1 == 1 ? opcode[i + 1] : opcode[opcode[i + 1]];

		if (mode_2 == 2) b = (long long int) opcode[relative_base + opcode[i + 2]];
		else b = mode_2 == 1 ? opcode[i + 2] : opcode[opcode[i + 2]];

		if (mode_3 == 2) c = relative_base + opcode[i + 3];
		else c = opcode[i + 3];

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
			if(mode_1 == 2) opcode[relative_base + opcode[i + 1]] = input;
			else opcode[opcode[i + 1]] = input;
			i += 2;
			break;
		case 4:
			if(isFirst) {
				map[pos] = a;
			} else {
				angle = a ? angle + 90 : angle - 90;
				moveForward(pos, angle);
				input = map[pos] == 1 ? 1 : 0;
			}
			isFirst = !isFirst;
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

		case 9:
			relative_base += a;
			i += 2;
			break;

		default:
			break;
		}
	}
}

int main() {
	std::vector<long long int> vec;
	vec.reserve(1000000);
	long long int n, input;
	char c;
	std::cout << "Input ID: ";
	std::cin >> input;
	while (std::cin >> n) {
		vec.push_back(n);
		std::cin >> c;
	}

	parse(input, vec);
	std::cout << map.size() << std::endl;

	std::ofstream outfile ("SecondPart.txt");
	for(int i = -50; i <=50; i++) {
		for(int j = 50; j >= -50; j-- ) {
			if(map[std::make_pair(i,j)]) outfile << "#";
			else outfile << ".";
		}
		outfile << "\n";
	}

	outfile.close();
	std::cout << "Output is written to SecondPart.txt" << std::endl;
}

