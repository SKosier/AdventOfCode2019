/*
 * day2.cpp
 *
 *  Created on: Dec 5, 2019
 *      Author: sanja
 */
#include <iostream>
#include <vector>

#define END 19690720

int function(std::vector<int>& vec, int first, int second)
{
	std::vector<int> sec(vec.begin(), vec.end());
	sec[1] = first;
	sec[2] = second;
	for(int i = 0; i < vec.size(); i=i+4)
	{
		int a = sec[i+1];
		int b = sec[i+2];
		int c = sec[i+3];

		if(sec[i] == 99) break;

		if(sec[i] == 1) {
			sec[c] = sec[a] + sec[b];
		}
		if(sec[i] == 2) {
			sec[c] = sec[a] * sec[b];
		}
	}
	return sec[0];
}

int main()
{
	std::vector<int> vec;
    int n;
    char c;
    while(std::cin >> n){
    	vec.push_back(n);
        std::cin >> c;
    }

	std::cout << function(vec, 12,2) << std::endl;

	for(int i = 0; i < 100; i++) {
		for(int j = 0; j < 100; j++) {
			if(function(vec, i, j) == END) std::cout << 100 * i + j << std::endl;
		}
	}
}


