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
	public:
		Node* start{ nullptr };

	public:

		Stack() = default;
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
		}

		Stack(const Stack& other) = delete;
		Stack& operator=(const Stack& other) = delete;

		void Push(const T& element)
		{
			Node* n = new Node(element, start);
			start = n;
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
				return true;
			}
			return false;
		}

		void Pop()
		{
			Node* current = start;
			start = current->next;

			delete current;
		}

	};
}