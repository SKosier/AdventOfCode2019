#include <iostream>

int get_fuel1(int num)
{
	if((num / 3) - 2 > 0) return (num/3)-2;
	return 0;
}

int get_fuel2(int num)
{
	int sum = 0;
	if((num/3) - 2 <= 0) return 0;

	return sum += (num/3) - 2 + get_fuel2((num/3) - 2);
}


int main()
{
	int num, sum1 = 0, sum2 = 0;
	while(std::cin >> num)
	{
		sum1 += get_fuel1(num);
		sum2 += get_fuel2(num);
	}
	std::cout << sum1 << std::endl;
	std::cout << sum2 << std::endl;
}
