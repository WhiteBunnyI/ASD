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
#include <list>

using ullong = unsigned long long;

namespace asd
{
	bool lab1(std::string& str)
	{
		asd::Stack<char> stack;

		//std::string str = "(){}[]()(()){()()}(([]))()()()(())()";

		//char str[10000];
		//std::cin.getline(str, 10000);
		//int len = std::strlen(str);

		if (str.size() == 0)
		{
			std::cout << "Строки не существует\n";
			return false;
		}

		int i;
		for (i = 0; i < str.size(); i++)
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
		if (i == str.size() && stack.Top() == nullptr)
		{
			//std::cout << "Строка правильная\n";
			return true;
		}

		//std::cout << "Строка неправильная\n";
		return false;
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
				size_t left = o;					//левая граница левого массива
				size_t right = left + i;			//левая граница правого массива
				size_t leftEnd = right;
				size_t rightEnd = right + i;
				bool leftValid = left != leftEnd && left < count;		//Проверка границ левого массива
				bool rightValid = right != rightEnd && right < count;	//Проверка границ правого массива
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
			lab11(temp);
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

	bool IsStrContainsChar(char* chars, char chr)
	{
		for (size_t i = 0; chars[i] != '\0'; i++)
		{
			if (chars[i] == chr)
				return true;
		}

		return false;
	}

	std::vector<int> convertStrToBinTree(std::string& str)
	{
		std::vector<int> tree(100);

		size_t currentNumIndex = 0;
		int currentNum = 0;

		auto writeNum = [&tree, &currentNumIndex, &currentNum](size_t newIndex)
			{
				if (currentNumIndex >= tree.size())
					tree.resize(currentNumIndex * 2);
				if (currentNum)
				{
					tree[currentNumIndex] = currentNum;
					currentNum = 0;
				}
				currentNumIndex = newIndex;
			};

		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] >= '0' && str[i] <= '9')
			{
				currentNum = currentNum * 10 + (str[i] - 48);
				continue;
			}

			if (str[i] == '(')
			{
				writeNum(2 * currentNumIndex + 1);
				continue;
			}

			if (str[i] == ',')
			{
				writeNum(currentNumIndex + 1);
				continue;
			}

			if (str[i] == ')')
			{
				writeNum((currentNumIndex - 2) / 2);
				continue;
			}
		}
		return tree;
	}

	//прямой
	void Direct(std::vector<int>& tree, size_t index = 0)
	{
		if (tree[index] == 0)
			return;
		std::cout << tree[index] << ' ';

		Direct(tree, index * 2 + 1);
		Direct(tree, index * 2 + 2);
	}

	//центральный
	void Center(std::vector<int>& tree, size_t index = 0)
	{
		if (tree[index] == 0)
			return;

		Center(tree, index * 2 + 1);

		std::cout << tree[index] << ' ';

		Center(tree, index * 2 + 2);
	}

	//Концевой
	void End(std::vector<int>& tree, size_t index = 0)
	{
		if (tree[index] == 0)
			return;

		End(tree, 2 * index + 1);
		End(tree, 2 * index + 2);

		std::cout << tree[index] << ' ';
	}

	//Рекурсивные обходы (прямой, центральный, концевой)
	void lab15(std::string& str)
	{
		std::vector<int> tree = convertStrToBinTree(str);
		for (size_t i = 0; i < tree.size(); i++)
		{
			std::cout << tree[i] << ' ';
		}
		std::cout << std::endl;
		Direct(tree);
		std::cout << std::endl;
		Center(tree);
		std::cout << std::endl;
		End(tree);
		std::cout << std::endl;
	}

	//Нерекурсивный обход (прямой)
	void lab16(std::string& str)
	{
		std::vector<int> tree = convertStrToBinTree(str);
		//for (size_t i = 0; i < tree.size(); i++)
		//{
		//	std::cout << tree[i] << ' ';
		//}
		//std::cout << std::endl;

		Stack<size_t> needToCheck;
		needToCheck.Push(0);

		while (needToCheck.Top())
		{
			size_t index = *needToCheck.Top();
			needToCheck.Pop();

			if (!tree[index]) 
				continue;

			std::cout << tree[index] << ' ';

			size_t next = 2 * index + 2;
			if (next < tree.size())
				needToCheck.Push(next);

			--next;
			needToCheck.Push(next);
				
		}
		std::cout << std::endl;
		
	}
	//-------------------------------------------------------------------------------------------
	void lab2(std::string& str)
	{

		auto GetNum = [](std::string& str, size_t& index)
			{
				std::string result;
				if (str[index] == '-')
				{
					result += '-';
					++index;
				}
				'0'; '9';
				while (str[index] >= 48 && str[index] <= 57)
				{
					result += str[index];
					++index;
				}
				return result;
			};

		if (!lab1(str))
		{
			std::cout << "Строка неправильная\n";
			return;
		}
		//Пройти проверки
		std::string main;
		Stack<char> stack;

		for (size_t i = 0; i < str.size(); i++)
		{
			const char* t;
			switch (str[i])
			{
			case '*':
			case '/':
				t = stack.Top();
				while (t)
				{
					if (*t == '(')
						break;
					if (*t == '*' || *t == '/')
					{
						main += *t;
						main += ' ';
						stack.Pop();
						t = stack.Top();
						continue;
					}
					break;
				}
				stack.Push(str[i]);
				break;

			case '+':
			case '-':
				if (i == 0 || str[i - 1] == '(')
				{
					main += GetNum(str, i) + " ";
					--i;
					continue;
				}
				t = stack.Top();
				while (t)
				{
					if (*t == '(')
						break;
					main += *t;
					main += ' ';
					stack.Pop();
					t = stack.Top();
				}
				stack.Push(str[i]);
				break;

			case '(':

				stack.Push(str[i]);
				break;

			case ')':
				t = stack.Top();
				while (*t != '(')
				{
					main += *stack.Top();
					main += ' ';

					stack.Pop();
					t = stack.Top();
				}
				stack.Pop();
				break;

			case '=':
				i = str.size();
				break;

			default:
				if (IsStrContainsChar("0123456789", str[i]))
				{
					main += GetNum(str, i) + " ";
					--i;
					break;
				}
				throw std::runtime_error("Unknown operator");
				break;
			}
		}

		while (stack.Top())
		{
			main += *stack.Top();
			main += ' ';
			stack.Pop();
		}
		std::cout << main << std::endl;
		Stack<float> temp;
		float num1;
		float num2;
		for (size_t i = 0; i < main.size(); i++)
		{
			if (main[i] == ' ')
				continue;

			if (!(main[i] == '-' && main[i + 1] == ' ') && !IsStrContainsChar("*/+", main[i]))
			{
				num1 = std::stoi(GetNum(main, i));
				temp.Push(num1);
				continue;
			}

			num2 = *temp.Top();
			temp.Pop();
			num1 = *temp.Top();
			temp.Pop();

			switch (main[i])
			{
			case '*':
				temp.Push(num1 * num2);
				break;

			case '/':
				if (!num2)
					throw std::runtime_error("Division by zero");
				temp.Push(num1 / num2);
				break;

			case '-':
				temp.Push(num1 - num2);
				break;

			case '+':
				temp.Push(num1 + num2);
				break;
			}

		}
		std::cout << *temp.Top();
	}

	void printTreeStr(std::vector<int>& tree, std::size_t index = 0)
	{
		if (tree[index] == 0)
			return;
		std::cout << tree[index];
		index = index * 2 + 1;
		bool isValid = (index + 1) < tree.size();
		bool isLeft = tree[index];
		bool isRight = tree[index + 1];
		bool isHas = isValid && (isLeft || isRight);

		if (isHas)
			std::cout << '(';

		if (isLeft)
		{
			printTreeStr(tree, index);
		}

		if (isHas)
			std::cout << ',';

		++index;
		if (isRight)
		{
			printTreeStr(tree, index);
		}

		if (isHas)
		{
			std::cout << ')';
		}
	}

	size_t GetTreeDepth(std::vector<int>& tree, size_t index = 0, size_t depth = 0)
	{
		if (tree[index] == 0)
			return depth;
		size_t dL, dR;
		++depth;
		dL = GetTreeDepth(tree, index * 2 + 1, depth);
		dR = GetTreeDepth(tree, index * 2 + 2, depth);
		return dL > dR ? dL : dR;
	}

	void OutTree(std::vector<int>& tree, std::vector<std::string>& out, size_t index = 0, size_t depth = 0)
	{
		if (tree[index] == 0)
			return;

		++depth;
		OutTree(tree, out, 2 * index + 1, depth);
		int under = out[depth].size();
		out[depth] += "   ";
		OutTree(tree, out, 2 * index + 2, depth);
		out[depth] += ' ';
		int cur = out[depth - 1].size();
		for (int i = 0; i < under - cur; i++)
		{
			out[depth - 1] += ' ';
		}

		out[depth - 1] += std::to_string(tree[index]);
	}


	void printTree(std::vector<int>& tree)
	{
		size_t depth = GetTreeDepth(tree);
		std::vector<std::string> out;

		for (size_t i = 0; i <= depth; i++)
		{
			out.push_back("");
		}

		OutTree(tree, out);

		for (int i = 0; i < depth; i++)
		{
			std::cout << out[i] << std::endl;
		}

		

		std::cout << std::endl;
		std::cout << "3   4 5   62   \n";
		std::cout << " \\ /   \\ /  \n";
		std::cout << "  7     8\n";
		std::cout << std::endl;

		std::cout << "";

	}

	void lab17(std::string& str)
	{
		std::vector<int> tree = convertStrToBinTree(str);
		int command = 4;
		/*printTree(tree);
		return;*/
		while (true)
		{
			size_t key;
			size_t index;
			int root;
			Stack<size_t> stack;

			if (command == 4)
			{
				system("cls");
				printTreeStr(tree);
				std::cout << std::endl;
			}

			std::cout << "\nВведите команду:\n1 (Поиск)\n2 (Добавить)\n3 (Удалить)\n4 (Вывести дерево)\n5 (Выйти)\n\n";
			std::cin >> command;
			
			switch (command)
			{
			case 1:
				std::cout << "Введите ключ для поиска: ";
				std::cin >> key;
				std::cout << std::endl;
				system("cls");
				if (key >= tree.size() || !tree[key])
				{
					std::cout << "Вершина не найдена\n";
					break;
				}
				std::cout << "Вершина найдена: " << tree[key] << std::endl;
				break;

			case 2:
				std::cout << "Введите элемент для добавления: ";
				std::cin >> root;
				std::cout << "\nВведите ключ вершины, к которому необходимо добавить элемент: ";
				std::cin >> key;
				std::cout << std::endl;
				system("cls");
				index = key * 2 + 1;

				if (index > tree.size())
					tree.resize(index);

				if (tree[index] && tree[index + 1])
				{
					std::cout << "Невозможно добавить данный элемент!\n";
					break;
				}

				if (!tree[index])
					tree[index] = root;
				else if(!tree[index + 1])
					tree[index + 1] = root;

				std::cout << "Элемент был успешно добавлен!\n";

				break;

			case 3:
				std::cout << "Введите ключ вершины для удаления: ";
				std::cin >> key;
				std::cout << std::endl;
				system("cls");

				if (!tree[key])
				{
					std::cout << "Вершины не существует!\n";
					break;
				}

				stack.Push(key);
				while (stack.Top())
				{
					index = *stack.Top();
					stack.Pop();
					if (!tree[index])
						continue;
					tree[index] = 0;
					stack.Push(index * 2 + 1);
					stack.Push(index * 2 + 2);
				}
				std::cout << "Вершина была удалена!\n";
				break;

			case 5:
				system("cls");
				printTreeStr(tree);
				std::cout << std::endl;
				system("exit");
				return;

			default:
				break;
			}
			

		}
	}

	class HashTable
	{
		const static size_t CONST = 10;
		using pair = std::pair<size_t, std::string>;
		std::vector<pair> table;
	public:
		HashTable() : table{ CONST,  } {};
		~HashTable() = default;
		HashTable(const HashTable& other) = delete;
		void operator=(const HashTable& other) = delete;

		size_t GetHash(const std::string& word)
		{
			size_t hash = 0;
			for (size_t i = 0; word[i] != '\0'; i++)
			{
				hash = (hash + word[i]) % CONST;
			}

			return hash;
		}

		size_t Push(const std::string& word)
		{
			pair a{ GetHash(word), word };
;
			for (size_t i = a.first; i < table.size(); i++)
			{
				if (table[i].second.empty())
				{
					table[i] = a;
					return i;
				}
				if (table[i].second == word)
					return i;
			}

			table.push_back(a);

			return table.size() - 1;
		}

		std::string Get(const size_t& hash)
		{
			return table[hash].second;
		}

		void Print()
		{
			std::cout << "Hash\t\tA.hash\t\tWord\n";
			for (size_t i = 0; i < table.size(); i++)
			{
				std::cout << i << "\t\t" << table[i].first << "\t\t" << table[i].second << '\n';
			}
		}
		
	};

	void lab13(char* filename)
	{
		HashTable table;
		std::ifstream input(filename);
		std::string word;
		while (!input.eof())
		{
			input >> word;
			table.Push(word);
		}

		table.Print();
	}
	
	class HashTableList
	{
		const static size_t CONST = 10;
		
		using list = std::list<std::string>;
		std::vector<list> table;
	public:
		using pair = std::pair<size_t, size_t>;
		HashTableList() : table{ CONST } {};
		~HashTableList() = default;
		HashTableList(const HashTableList& other) = delete;
		void operator=(const HashTableList& other) = delete;

		size_t GetHash(const std::string& word)
		{
			size_t hash = 0;
			for (size_t i = 0; word[i] != '\0'; i++)
			{
				hash = (hash + word[i]) % CONST;
			}

			return hash;
		}

		pair Push(const std::string& word)
		{
			size_t hash = GetHash(word);
			size_t index = 0;
			for (auto l = table[hash].begin(); l != table[hash].end(); ++l)
			{
				if (*l == word)
				{
					return { hash, index };
				}
				++index;
			}
			table[hash].push_back(word);
			return { hash, table[hash].size() - 1 };
			//table[GetHash(word)].push_front(word);
		}

		std::string Get(const pair& hash)
		{
			auto p = table[hash.first].begin();
			for (size_t i = 0; i < hash.second; i++)
			{
				++p;
			}
			return *p;
		}

		void Print()
		{
			std::cout << "hash\t\twords\n";
			for (size_t i = 0; i < table.size(); i++)
			{
				if (table[i].empty()) continue;
				std::cout << i << "\t\t" << *table[i].begin() << std::endl;
				for (auto l = ++table[i].begin(); l != table[i].end(); l++)
				{
					std::cout << "\t\t" << *l << std::endl;
				}
			}
		}
	};

	void printPair(HashTableList& table, HashTableList::pair p)
	{
		std::cout << p.first << ' ' << p.second << " In table: " << table.Get(p) << std::endl;
	}

	void lab14(char* filename)
	{
		HashTableList table;
		std::ifstream input(filename);
		std::string word;
		
		while (!input.eof())
		{
			input >> word;
			table.Push(word);
		}

		table.Print();
	}
}