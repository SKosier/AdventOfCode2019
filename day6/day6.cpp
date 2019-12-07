/*
 * day6.cpp
 *
 *  Created on: Dec 6, 2019
 *      Author: sanja
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

std::unordered_map<std::string, std::vector<std::string>> map;
std::unordered_map<std::string, std::string> map_parents;
std::unordered_set<std::string> visited;

int countOrbits(std::string s, int depth)
{
	int sum = 0;
	for(std::string str : map[s])
	{
		sum += countOrbits(str, depth+1) + depth + 1 ;
	}
	return sum;
}

int countPath(std::string you, std::string san)
{
	std::vector<std::string> parents_of_you;
	std::vector<std::string> parents_of_san;

	while(map_parents[you] != "COM")
	{
		parents_of_you.push_back(you);
		you = map_parents[you];
	}

	while (map_parents[san] != "COM")
	{
		parents_of_san.push_back(san);
		san = map_parents[san];
	}

	for(auto i = parents_of_you.begin(); i != parents_of_you.end(); i++)
	{
		for(auto j = parents_of_san.begin(); j != parents_of_san.end(); j++)
		{
			if(*i == *j)
			{
				return std::distance(parents_of_you.begin(), i) + std::distance(parents_of_san.begin(), j) - 2;
			}
		}
	}
}

int main ()
{
	std::string line;
    std::ifstream file("input.txt");
	while (std::getline(file, line)) {
		std::string first = line.substr(0, 3);
		if(map.find(first) != map.end()) {
			map[first].push_back(line.substr(4,3));

		} else {
			std::vector<std::string> vec;
			vec.push_back(line.substr(4,3));
			map[first] = vec;
		}

		std::string sec = line.substr(4,3);
		map_parents[sec] = first;
	}
	std::cout << countOrbits("COM", 0) << std::endl;
	std::cout << countPath("YOU", "SAN") << std::endl;
}
