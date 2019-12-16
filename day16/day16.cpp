/*
 * day16.cpp
 *
 *  Created on: Dec 16, 2019
 *      Author: sanja
 */
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <array>
#include <cmath>
#include <sstream>

const int noOfPhases = 100;
const int noOfRepeats = 10000;
static const std::array<int, 4> pattern = { 0, 1, 0, -1 };

void adjustPattern(std::vector<int> &vec, int element)
{
	int patternIndex = 0;
	for (int i = 0; i < vec.size(); i = i + element)
	{
		for (int j = 0; j < element; j++)
		{
			if (i + j >= vec.size()) return;
			vec[i + j] = pattern[patternIndex % 4];
		}
		++patternIndex;
	}
}

std::string repeat(int n, std::string s)
{
	std::ostringstream os;
	for (int i = 0; i < n; i++) os << s;
	return os.str();
}

void FFT(std::string line) {
	std::vector<int> pattern(line.size() + 1);
	std::vector<int> vec(line.size());
	for (int i = 0; i < line.size(); i++)
	{
		vec[i] = line[i] - '0';
	}

	for (int phase = 1; phase <= noOfPhases; phase++)
	{
		for (int i = 0; i < line.size(); i++)
		{
			adjustPattern(pattern, i + 1);
			int sum = 0;
			for (int j = 0; j < vec.size(); j++)
			{
				sum += vec[j] * pattern[j + 1];
			}

			vec[i] = std::abs(sum % 10);
		}
	}

	std::cout << "First part: ";
	for (int i = 0; i < 8; i++)
	{
		std::cout << vec[i];
	}
	std::cout << "\n";
}

void partTwo(std::string string)
{
	for (int phase = 1; phase <= noOfPhases; phase++)
	{
		int sum = 0;
		for (int i = string.size() - 1; i >= 0; i--)
		{
			sum = (sum + (string[i] - '0')) % 10;
			string[i] = sum + '0';
		}
	}
	std::cout << "Second part: " << string.substr(0,8) << std::endl;
}

int main() {
	std::string line;
	std::cin >> line;
	FFT(line);

	int offset = stoi(line.substr(0, 7));
	std::string repeatedString = repeat(noOfRepeats, line);
	partTwo(repeatedString.substr(offset, repeatedString.size() - offset));
}

