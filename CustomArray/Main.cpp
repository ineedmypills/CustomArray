#include "CustomArray.hpp"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CustomArray a(5);
	std::cin >> a;
	std::cout << a << std::endl;
	a++;
	std::cout << a << std::endl;
	a += 2;
	std::cout << a << std::endl;

	CustomArray b{ 5,4,3,2,1 };
	std::cout << b << std::endl;
	b = a;
	std::cout << b << std::endl;


	return 0;
}