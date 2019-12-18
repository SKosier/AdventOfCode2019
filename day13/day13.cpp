/*
 * day13.cpp
 *
 *  Created on: Dec 13, 2019
 *      Author: sanja
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <iterator>

const int END_X = -1;
const int END_Y = 0;
const int PADDLE = 3;
const int BALL = 4;

long long int parse(long long int input, std::vector<long long int> opcode)
{
	long long int i = 0, relative_base = 0;
	int index = 1, blocks = 0;;
	std::vector<std::vector<int>> objects;
	std::vector<int> current;
	current.resize(3);

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
			current[index%3] = a;
			if(index%3 == 0)
			{
				objects.push_back(current);
				if(a == 2) ++blocks;
			}

			++index;
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
	return blocks;
}

long long int parse_2(long long int input, std::vector<long long int> opcode)
{
	long long int i = 0, relative_base = 0;
	int index = 1, points = 0, paddle, ball, x, y;

	opcode[0] = 2;

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
			if(index % 3 == 1)
			{
				x = a;
			}
			else if(index % 3 == 2)
			{
				y = a;
			}
			else
			{
				paddle = a == PADDLE ? x : paddle;
				ball = a == BALL ? x : ball;
				points = (x == END_X && y == END_Y) ? a : points;
			}
			input = (paddle < ball) ? 1 : (paddle > ball) ? -1 : 0;

			++index;
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
	return points;
}

int main() {
	const std::string input_file{ "input.txt" };
	std::ifstream ifs(input_file);
	std::vector<long long> vec{ std::istream_iterator<long long>(ifs), std::istream_iterator<long long>() };
	vec.resize(100000);

	std::cout << parse(0, vec) << std::endl;
	std::cout << parse_2(0, vec) << std::endl;
}
