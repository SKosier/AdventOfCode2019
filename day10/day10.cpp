/*
 * day10.cpp
 *
 *  Created on: Dec 10, 2019
 *      Author: sanja
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <cmath>
#include <algorithm>

const int noOfVaporized = 200;
std::pair<int, int> laser;

//for putting angle in range (0, 360)
double calculate_angle(std::pair<int, int> laser, std::pair<int, int> asteroid)
{
    int delta_x = abs(asteroid.first - laser.first);
    int delta_y = abs(asteroid.second - laser.second);
    double angle = atan((double) delta_y / (double) delta_x) * 180.0 / (atan(1) * 4);

    if (delta_y == 0)
    {
        if (asteroid.first < laser.first) angle = 0.0;
        else angle = 180.0;
    }
    else if (delta_x == 0)
    {
        if (asteroid.second > laser.second) angle = 90.0;
        else angle = 270.0;
    }
    else
    {
        if (asteroid.first < laser.first)
        {
            if (asteroid.second < laser.second) angle += 270.0;
            else angle = 90.0 - angle;
        }
        else
        {
            if (asteroid.second < laser.second) angle = 270.0 - angle;
            else angle += 90.0;
        }
    }
    return angle;
}

int main() {
	std::vector<std::pair<int, int>> asteroids;
	std::string line;
	int length;

	std::ifstream input;
	input.open("input.txt");

	int row = 0;
	while (std::getline(input,line))
	{
		for(int j = 0; j < line.length(); j++) {
			if(line[j] == '#') asteroids.push_back(std::make_pair(j, row));
		}
		++row;
	}


	int max = -1, index;
	for (int i = 0; i < asteroids.size(); i++)
	{
		std::vector<double> lines;
		for (int j = 0; j < asteroids.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			lines.push_back(
					std::atan2(
							(double) asteroids[j].second - asteroids[i].second,
							(double) asteroids[j].first - asteroids[i].first));
		}

		std::sort(lines.begin(), lines.end());
		auto it = std::unique(lines.begin(), lines.end());
		int num = std::distance(lines.begin(), it);
		if (num > max)
		{
			max = num;
			index = i;
		}
	}

	std::cout << max << std::endl;
	laser = asteroids[index];

	std::map<double, std::vector<std::pair<int, int>>> map;
	for (std::pair<int, int> p : asteroids) {
		if (p == asteroids[index])
		{
			continue;
		}
		double angle = calculate_angle(laser, p);
		std::map<double, std::vector<std::pair<int, int>>>::iterator it = map.find(angle);

		if (it != map.end())
		{
			map[angle].push_back(p);
		}
		else
		{
			std::vector<std::pair<int, int>> vec;
			vec.push_back(p);
			map[angle] = vec;
		}
	}

	for (std::map<double, std::vector<std::pair<int, int>>>::iterator it = map.begin(); it != map.end(); ++it)
	{
		std::sort(it->second.begin(), it->second.end(),
				[](const std::pair<int, int> &p1, const std::pair<int, int> &p2)
				{
					return std::hypot(p1.first - laser.first, p1.second - laser.second)
							< std::hypot(p2.first - laser.first, p2.second - laser.second);
				});
	}

	int removed = 1;
	while (true)
	{
		for (std::map<double, std::vector<std::pair<int, int>>>::iterator it = map.begin(); it != map.end(); ++it)
		{
			std::vector<std::pair<int, int>> vec = it->second;
			if (vec.size() == 0)
				continue;

			if (removed == noOfVaporized)
			{
				std::cout << 100 * vec[0].first + vec[0].second << std::endl;
				return 1;
			}

			++removed;
			it->second.erase(it->second.begin());
		}
	}
}

