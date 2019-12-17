/*
 * day15.cpp
 *
 *  Created on: Dec 15, 2019
 *      Author: sanja
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

struct Position {
	int x;
	int y;

	bool operator==(const Position other) const {
		return std::tie(x, y) == std::tie(other.x, other.y);
	}
	bool operator<(const Position other) const {
		return std::tie(x, y) < std::tie(other.x, other.y);
	}
	bool operator>(const Position other) const {
		return std::tie(x, y) > std::tie(other.x, other.y);
	}
};

std::vector<long long int> opcode;
long long int index = 0;

int parse(int input) {
	long long int i = 0, relative_base = 0, output;

	while (opcode[i] != 99) {
		int opc = opcode[i] % 100;
		int mode_1 = (opcode[i] / 100) % 10;
		int mode_2 = (opcode[i] / 1000) % 10;
		int mode_3 = (opcode[i] / 10000) % 10;

		long long int a, b, c;

		if (mode_1 == 2) a = (long long int) opcode[relative_base + opcode[i + 1]];
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
			if (mode_1 == 2)
				opcode[relative_base + opcode[i + 1]] = input;
			else
				opcode[opcode[i + 1]] = input;
			i += 2;
			break;
		case 4:
			i += 2;
			return a;
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
	return output;
}

static const std::array<int, 4> directions = { 1, 2, 3, 4 };
static const std::array<int, 4> goBack = { 2, 1, 4, 3 };

Position move(Position pos, int direction) {
	if (direction == 1)
		--pos.y;
	if (direction == 2)
		++pos.y;
	if (direction == 3)
		--pos.x;
	if (direction == 4)
		++pos.x;
	return pos;
}

std::set<Position> walls;
std::set<Position> visited;
int steps = 0;
int openLocations = 0;
Position position { 0, 0 };
Position o2;

void findO2(int direction) {
	Position current = move(position, direction);
	if (visited.count(current) == 1 || walls.count(current) == 1) return;

	int output = parse(direction);
	if(output == 0) {
		walls.insert(current);
		return;
	}

	++steps;
	++openLocations;
	position = move(position, direction);
	visited.insert(position);

	if(output == 2) {
		o2 = position;
		std::cout << steps << " steps to reach O2" << std::endl;
	}

	for (auto dir : directions) {
		findO2(dir);
	}

	--steps;
	visited.erase(position);
	position = move(position, goBack[direction-1]);
	parse(goBack[direction-1]);
}

int minutes = 0;
void countMinutes(std::set<Position>& withOxygen, Position current, int current_minutes) {
	if(walls.count(current) >= 1) return;
	if(withOxygen.count(current) >= 1) return;

	minutes = current_minutes > minutes ? current_minutes : minutes;
	withOxygen.insert(current);
	if(withOxygen.size() == openLocations) {
		std::cout << minutes << " minutes and the room is filled with O2" << std::endl;
		return;
	}

	for(int dir : directions) {
		countMinutes(withOxygen, move(current, dir), current_minutes+1);
	}
}

int main() {
	long long int n, input;
	char c;
	opcode.reserve(1000000);
	while (std::cin >> n) {
		opcode.push_back(n);
		std::cin >> c;
	}

	for (auto dir : directions) {
		findO2(dir);
	}

	std::set<Position> withOxygen;
	countMinutes(withOxygen, o2, minutes);
}

