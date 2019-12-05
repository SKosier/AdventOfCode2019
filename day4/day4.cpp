/*
 * day4.cpp
 *
 *  Created on: Dec 4, 2019
 *      Author: sanja
 */
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
int first = 152085;
int second = 670283;

std::vector<int> get_digits(int num) {
	std::vector<int> dig;
	while (num != 0) {
		dig.push_back(num % 10);
		num /= 10;
	}
	return dig;
}

bool isDec(std::vector<int> &digits) {
	for (int i = 0; i < digits.size(); i++) {
		if (digits[i] < digits[i + 1])
			return false;
	}
	return true;
}

bool hasMatch(std::vector<int> &digits) {
	for (int i = 0; i < digits.size(); i++) {
		if (digits[i] == digits[i + 1])
			return true;
	}
	return false;
}

bool secondPart(std::vector<int> &vec) {
	for(int i = 0; i < vec.size(); i++) {
		if(std::count(vec.begin(), vec.end(), vec[i]) == 2) return true;
	}
	return false;
}

int main() {
	int cnt1 = 0, cnt2 = 0;
	std::vector<int> newOnes;
	for (int i = first; i <= second; i++) {
		std::vector<int> digits = get_digits(i);
		if (isDec(digits) && hasMatch(digits)) {
			cnt1++;
			if (secondPart(digits)) {
				cnt2++;
			}
		}
	}

	std::cout << cnt1 << std::endl;
	std::cout << cnt2 << std::endl;
}

