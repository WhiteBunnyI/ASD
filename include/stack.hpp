#pragma once

namespace asd
{
	template<typename T>
	class Stack
	{
		struct Node
		{
			T element;
			Node* next = nullptr;

			Node(const T& el, Node* nextNode)
			{
				element = el;
				next = nextNode;
			}
		};

		size_t m_count;
		Node* start{ nullptr };
	public:

		Stack() : m_count{ 0 } {}
		~Stack()
		{
			if (start == nullptr)
				return;

			Node* next;
			while (start->next != nullptr)
			{
				next = start->next;
				delete start;
				start = next;
			}
			delete start;
		}

		Stack(const Stack& other) = delete;
		Stack& operator=(const Stack& other) = delete;

		void Push(const T& element)
		{
			Node* n = new Node(element, start);
			start = n;
			++m_count;
		}

		const T* Top()
		{
			if(start != nullptr)
				return &start->element;
			return nullptr;
		}

		bool TryPop(T& out)
		{
			if (start != nullptr)
			{
				out = start->element;
				--m_count;
				return true;
			}
			return false;
		}

		void Pop()
		{
			Node* current = start;
			start = current->next;
			delete current;
			--m_count;
		}

		size_t Size()
		{
			return m_count;
		}
	};

	template<typename T>
	class Queue
	{
		struct Node
		{
			T element;
			Node* next = nullptr;

			Node(const T& el, Node* nextNode)
			{
				element = el;
				next = nextNode;
			}
		};

		size_t m_count{ 0 };
		Node* start{ nullptr };
		Node* end{ nullptr };

	public:

		Queue() = default;
		~Queue()
		{
			if (start == nullptr)
				return;

			Node* next;
			while (start->next != nullptr)
			{
				next = start->next;
				delete start;
				start = next;
			}
			delete start;
		}

		T* Get()
		{
			if (start)
				return &start->element;
			return nullptr;
		}

		void Pop()
		{
			if (start)
			{
				if (start == end)
					end = nullptr;
				Node* next = start->next;
				delete start;
				start = next;
				--m_count;
				
			}
		}

		void Push(const T& element)
		{
			++m_count;
			if (end)
			{
				end->next = new Node(element, nullptr);
				end = end->next;
				return;
			}

			start = new Node(element, nullptr);
			end = start;

		}

		size_t Size()
		{
			return m_count;
		}

	};
}