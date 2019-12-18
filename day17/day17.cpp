/*
 * day17.cpp
 *
 *  Created on: Dec 17, 2019
 *      Author: sanja
 */
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

const int size_of_m = 60;

char matrix[size_of_m][size_of_m];
int row, column;

long long int parse(long long int input, std::vector<long long int> opcode) {
	long long int i = 0, relative_base = 0;

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
			if(a == 10) {
				column = 0;
				row++;
			} else {
				matrix[row][column] = (char) a;
				++column;
			}
			std::cout << (char)a;
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

long long int parse_2(std::vector<long long int> input, std::vector<long long int> opcode) {
	long long int i = 0, relative_base = 0, input_index = 0;
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
			if(mode_1 == 2) opcode[relative_base + opcode[i + 1]] = input[input_index++];
			else opcode[opcode[i + 1]] = input[input_index++];
			i += 2;
			break;
		case 4:
			if(a > 127) return a;
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

int collect_Dust(std::vector<long long int> opcode)
{
	std::string main_routine = "A,A,C,B,C,B,C,B,A,B\n";
	std::string a = "R,6,L,8,R,8\n";
	std::string b = "L,8,R,6,L,10,L,10\n";
	std::string c = "R,4,R,6,R,6,R,4,R,4\n";
	std::string video = "n\n";
	std::string all = main_routine + a + b + c + video;

	std::vector<long long int> input_data;
	input_data.reserve(all.size());
	for (char c : all)
	{
		input_data.push_back(static_cast<long long int>(c));
	}

	return parse_2(input_data, opcode);
}

bool isIntersection(int i, int j)
{
	return matrix[i][j+1] == '#' && matrix[i][j-1] == '#' && matrix[i+1][j] == '#' && matrix[i-1][j] == '#';
}

int find_Intersections()
{
	int sum = 0;
	for(int i = 0; i < size_of_m; i++)
	{
		for(int j = 0; j < size_of_m; j++)
		{
			if(matrix[i][j] == '#' && isIntersection(i, j))
				sum += i*j;
		}
	}
	return sum;
}

int main() {
	const std::string input_file{ "input.txt" };
	std::ifstream ifs(input_file);
	std::vector<long long> vec{ std::istream_iterator<long long>(ifs), std::istream_iterator<long long>() };
	vec.resize(100000);

	parse(0, vec);
	std::cout << find_Intersections() << std::endl;
	std::cout << collect_Dust(vec) << std::endl;
}



