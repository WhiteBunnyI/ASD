#pragma once

#include <stack.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <filesystem>

using ullong = unsigned long long;

namespace asd
{
	void lab1()
	{
		asd::Stack<char> stack;

		std::cout << "Введите строку:\n";

		//std::string str = "(){}[]()(()){()()}(([]))()()()(())()";

		char str[10000];
		std::cin.getline(str, 10000);
		int len = std::strlen(str);

		if (len == 0)
		{
			std::cout << "Строки не существует\n";
			return;
		}

		int i;
		for (i = 0; i < len; i++)
		{
			char chr = str[i];
			if (chr == '(' || chr == '{' || chr == '[')
			{
				stack.Push(chr);
				continue;
			}

			char top;
			if (chr == ')' || chr == '}' || chr == ']')
			{
				if (stack.TryPop(top))
				{
					if (chr == ')' && top == '(')
					{
						stack.Pop();
						continue;
					}
					if (chr == '}' && top == '{')
					{
						stack.Pop();
						continue;
					}
					if (chr == ']' && top == '[')
					{
						stack.Pop();
						continue;
					}
				}
				break;
			}
		}


		//Прочитали все строку и ничего не осталось в стеке
		if (i == len && stack.Top() == nullptr)
		{
			std::cout << "Строка правильная\n";
			return;
		}

		std::cout << "Строка неправильная\n";
	}

	bool compareLab3(std::pair<std::string, ullong>& left, std::pair<std::string, ullong>& right)
	{
		return left.second < right.second;
	}

	void lab3()
	{
		unsigned long long x;
		std::cout << "Введите число x:\n";
		std::cin >> x;

		int l_x = log(x);
		int m_k = l_x / log(3);
		int m_l = l_x / log(5);
		int m_m = l_x / log(7);

		std::vector < std::pair < std::string, ullong> > vec;

		for (int k = 0; k < m_k; k++)
		{
			for (int l = 0; l < m_l; l++)
			{
				for (int m = 0; m < m_m; m++)
				{
					ullong res = powl(3, k) * pow(5, l) * pow(7, m);
					std::string s = std::to_string(k) + '\t' + std::to_string(l) + '\t' + std::to_string(m) + '\t';
					if(res < x)
						vec.emplace_back(s, res);
				}
			}
		}
		
		std::sort(vec.begin(), vec.end(), compareLab3);

		std::cout << "k:\tl:\tm:\tr:\n";
		for each (auto var in vec)
		{
			std::cout << var.first << " " << var.second << std::endl;
		}
	}

	void lab4(std::vector<int>& data)
	{
		float factor = 0.85f;

		int step = data.size() - 1;

		while (step >= 1)
		{
			for (int i = 0; i + step < data.size(); i++)
			{
				if (data[i] > data[i + step])
				{
					std::swap(data[i], data[i + step]);
				}
			}
			step *= factor;
		}
	}

	void lab5(std::vector<int>& data)
	{
		for (int i = 1; i < data.size(); i++)
		{
			int pos = i;
			for (int o = i - 1; o >= 0; o--)
			{
				if (data[pos] < data[o])
				{
					std::swap(data[pos], data[o]);
					pos = o;
				}
			}
		}

	}

	void lab6(std::vector<int>& data)
	{
		for (int i = 0; i < data.size(); i++)
		{
			int minimum = i;
			for (int o = i + 1; o < data.size(); o++)
			{
				if (data[minimum] > data[o])
					minimum = o;
			}
			if(i != minimum)
				std::swap(data[i], data[minimum]);
		}
	}

	//--------------------------------------- Сдано 19.09.24

	void lab7(std::vector<int>& data)
	{
		int d = data.size() / 2;

		for (int d = data.size() / 2; d >= 1; d /= 2)
		{
			for (int i = d; i < data.size(); i++)
			{
				int bigger = i;
				for (int o = i - d; o >= 0; o--)
				{
					if (data[bigger] < data[o])
					{
						std::swap(data[bigger], data[o]);
						bigger = o;
						continue;
					}

					break;
				}
			}
		}
	}

	void lab8(std::vector<int>& data)
	{	
		std::vector<int> temp[10];
		int r = 1;
		bool b = true;
		while (b)
		{
			b = false;
			for (int i = 0; i < data.size(); i++)
			{
				int n = (data[i] / r) % 10; // Получаем разряд 
				n ? b = true : b;

				temp[n].push_back(data[i]);
			}
			
			data.clear();

			//Записываем в исходный массив
			for (int i = 0; i < 10; i++)
			{
				for (int o = 0; o < temp[i].size(); o++)
				{
					data.push_back(temp[i][o]);
				}
				temp[i].clear();
			}
			//Ставим на чтение следующий разряд
			r*=10;
		}
	}

	bool heapify(std::vector<int>& data, int i, bool isChanged)
	{
		if (i == 0)
			return isChanged;

		int c = i;

		if (i % 2)
			c = c / 2;
		else
			c = (c - 2) / 2;

		if (data[c] < data[i])
		{
			std::swap(data[c], data[i]);
			isChanged = true;
		}
		return heapify(data, c, isChanged);
	}

	void lab9(std::vector<int>& data)
	{
		int count = data.size();
		for (int o = 0; o < count; o++)
		{
			for (int i = (count - o) / 2; i < count - o; i++)
			{
				while (heapify(data, i, false));
			}
			std::swap(data[0], data[count - 1 - o]);
		}
	}

	void lab10(std::vector<int>& data)
	{
		size_t count = data.size();
		for (size_t i = 1; i < count; i*=2) //Кол-во элементов в разделенном массиве
		{
			std::vector<int> temp;
			size_t size = 2 * i;
			for (size_t o = 0; o < count; o += size) //Текущий левый массив
			{
				size_t left = o;
				size_t right = left + i;
				size_t leftEnd = right;
				size_t rightEnd = right + i;
				bool rightValid = right != rightEnd && right < count;
				bool leftValid = left != leftEnd && left < count;
				while (rightValid || leftValid)
				{
					rightValid = right != rightEnd && right < count;
					leftValid = left != leftEnd && left < count;

					if (rightValid && leftValid)
					{
						if (data[left] < data[right])
						{
							temp.push_back(data[left]);
							++left;
						}
						else
						{
							temp.push_back(data[right]);
							++right;
						}
					}
					else if (rightValid)
					{
						temp.push_back(data[right]);
						++right;
					}
					else if (leftValid)
					{
						temp.push_back(data[left]);
						++left;
					}
				}
			}
			data = temp;
		}
	}

	void QuickSort(std::vector<int>& data, size_t first, size_t last)
	{
		if (last - first <= 1) return;
		size_t pivot = last - 1;
		size_t wall = first;

		for (size_t i = first; i < last; i++)
		{
			if (data[pivot] > data[i])
			{
				std::swap(data[wall], data[i]);
				++wall;
				continue;
			}

		}

		std::swap(data[wall], data[pivot]);

		QuickSort(data, first, wall);
		QuickSort(data, wall + 1, last);
	}

	void lab11(std::vector<int>& data)
	{
		QuickSort(data, 0, data.size());
	}	

	void lab12(std::string filename)
	{
		const size_t read = 4096;

		std::ifstream input1(filename);
		std::ifstream input2;
		std::ofstream out;

		std::vector<int> temp;
		size_t current = 0;

		std::filesystem::create_directory("./tempDir/");

		while (!input1.eof())
		{
			temp.resize(read);
			size_t count = 0;
			for (; count < read && !input1.eof(); count++)
			{
				input1 >> temp[count];
			}

			temp.resize(count);
			lab10(temp);
			out.open("./tempDir/0temp" + std::to_string(current));

			for (size_t i = 0; i < count; i++)
			{
				out << temp[i] << ' ';
			}

			out.close();
			temp.clear();
			++current;
		}
		input1.close();

		size_t cycle = 0;
		while (current != 1)
		{
			size_t i = 0;
			for (; i < current / 2; i++)
			{
				input1.open("./tempDir/" + std::to_string(cycle) + "temp" + std::to_string(i*2));
				input2.open("./tempDir/" + std::to_string(cycle) + "temp" + std::to_string(i*2 + 1));
				out.open("./tempDir/" + std::to_string(cycle + 1) + "temp" + std::to_string(i));
				int t1;
				int t2;
				input1 >> t1;
				input2 >> t2;

				bool isOpen1 = !input1.eof();
				bool isOpen2 = !input2.eof();

				while (isOpen1 || isOpen2)
				{
					if (isOpen1 && isOpen2)
					{
						if (t1 < t2)
						{
							out << t1 << ' ';
							input1 >> t1;
							isOpen1 = !input1.eof();
						}
						else
						{
							out << t2 << ' ';
							input2 >> t2;
							isOpen2 = !input2.eof();
						}
					}
					else if (isOpen1)
					{
						out << t1 << ' ';
						input1 >> t1;
						isOpen1 = !input1.eof();
					}
					else
					{
						out << t2 << ' ';
						input2 >> t2;
						isOpen2 = !input2.eof();
					}

				}
				input1.close();
				input2.close();
				out.close();
			}
			if (current % 2)
			{
				std::filesystem::rename("./tempDir/" + std::to_string(cycle) + "temp" + std::to_string(i*2), "./tempDir/" + std::to_string(cycle + 1) + "temp" + std::to_string(current / 2));
				++current;
			}
			++cycle;
			current /= 2;
		}

		std::filesystem::rename("./tempDir/" + std::to_string(cycle) + "temp" + '0', "./result.txt");
		std::filesystem::remove_all("./tempDir");
	}

	void lab15(std::string str)
	{
		std::vector<int> temp;
		for (size_t i = 0; i < str.size(); i++)
		{

		}

	}
}