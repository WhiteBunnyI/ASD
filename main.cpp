#include <labs.hpp>
#include <functional>

bool Check(std::vector<int>& data)
{
	bool isRight = true;
	int prev = data[0];
	for each (auto var in data)
	{
		std::cout << var << ' ';
		if (prev > var)
			isRight = false;
	}
	return isRight;
}

void Test(std::vector<int>& data)
{
	if (Check(data))
	{
		std::cout << "\tpassed the test\n";
	}
	else
	{
		std::cout << "\tfailed the test\n";
	}
}

void Test12Lab()
{
	//Внешняя многофазная

	//100 000 
	asd::lab12("sorting.txt");
	std::ifstream input("./result.txt");

	int prev;
	input >> prev;
	int current;

	while (!input.eof())
	{
		input >> current;
		if (prev >= current)
		{
			std::cout << "Test failed!\n";
			return;
		}
	}
	std::cout << "Test complete!\n";
	//Внешняя многофазная
}

void Test2Lab()
{
	std::string str = "-20+7*(3/9)-(-5)*(0-1)=";
	asd::lab2(str);
}

void Test15Lab()
{
	std::string str = "8(3(1,6(4,7)),10(,14(13,)))";
	asd::lab15(str);
}

int main()
{
	std::setlocale(LC_ALL, "rus");

	//Test2Lab();
	//Test12Lab();
	Test15Lab();
	return 0;
	
	std::vector<int> data1{ 2,4,5,1,10,3,6,8,7,9 };
	std::vector<int> data2{ 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> data3{ 10,9,8,7,6,5,4,3,2,1 };
	std::vector<int> data4{ 32,95,16,82,24,66,35,19,75,54,40,43,93,68 };
	std::vector<int> data5{ 1,3,2,1,2,3,4,5,6,9 };

	std::function<void(std::vector<int>&)> func = asd::lab10;

	func(data1);
	func(data2);
	func(data3);
	func(data4);
	func(data5);

	Test(data1);
	Test(data2);
	Test(data3);
	Test(data4);
	Test(data5);

}