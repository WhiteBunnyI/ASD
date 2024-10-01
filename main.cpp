#include <labs.hpp>
#include <functional>

int main()
{
	std::setlocale(LC_ALL, "rus");

	//100 000 
	asd::lab12("sorting.txt");

	return 0;
	std::vector<int> data1{ 2,4,5,1,10,3,6,8,7,9 };
	std::vector<int> data2{ 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> data3{ 10,9,8,7,6,5,4,3,2,1 };
	std::vector<int> data4{ 32,95,16,82,24,66,35,19,75,54,40,43,93,68 };
	std::vector<int> data5{ 1,3,2,1,2,3,4,5,6,9 };

	std::function<void(std::vector<int>&)> func = asd::lab11;

	func(data1);
	func(data2);
	func(data3);
	func(data4);
	func(data5);

	for each (auto var in data1)
	{
		std::cout << var << ' ';
	}
	std::cout << std::endl;

	for each (auto var in data2)
	{
		std::cout << var << ' ';
	}
	std::cout << std::endl;

	for each (auto var in data3)
	{
		std::cout << var << ' ';
	}
	std::cout << std::endl;

	for each (auto var in data4)
	{
		std::cout << var << ' ';
	}
	std::cout << std::endl;

	for each (auto var in data5)
	{
		std::cout << var << ' ';
	}
	std::cout << std::endl;
}