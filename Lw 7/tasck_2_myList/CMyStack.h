#pragma once

#include <cstddef>
#include <memory>

template <typename T>
class CMyStack
{
	struct MyNode
	{
		MyNode(const T& value, const std::shared_ptr<MyNode>& next = nullptr)
			: value(value)
			, next(next){};

		T value;
		std::shared_ptr<MyNode> next;
	};

public:
	CMyStack() = default;

	CMyStack(const CMyStack& other)
	{
		*this = other;
	}

	CMyStack(CMyStack&& other)
		: m_top(other.m_top)
		, m_size(other.m_size)
	{
		other.m_top = nullptr;
		other.m_size = 0;
	}

	void Push(const T& element)
	{
		m_top = std::make_shared<MyNode>(element, m_top);
		++m_size;
	}

	void Pop()
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}

		m_top = m_top->next;
		--m_size;
	}

	T GetElement() const
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}

		return m_top->value;
	}

	bool IsEmpty() const
	{
		return !m_top;
	}

	void Clear()
	{
		while (m_top != nullptr)
		{
			m_top = m_top->next;
		}

		m_size = 0;
	}

	std::size_t GetSize() const
	{
		return m_size;
	}

	CMyStack& operator=(const CMyStack& right)
	{
		if (std::addressof(right) != this && !right.IsEmpty())
		{
			std::shared_ptr<MyNode> tmp = right.m_top;
			std::shared_ptr<MyNode> currentElement = std::make_shared<MyNode>(tmp->value);
			m_top = currentElement;

			tmp = tmp->next;
			//++m_size;

			while (tmp != nullptr)
			{
				currentElement->next = std::make_shared<MyNode>(tmp->value);
				currentElement = currentElement->next;

				tmp = tmp->next;
				//++m_size;
			}

			m_size = right.m_size;
		}

		if (right.IsEmpty())
		{
			Clear();
		}

		return *this;
	}

	CMyStack& operator=(CMyStack&& right)
	{
		m_top = right.m_top;
		m_size = right.m_size;

		right.m_top = nullptr;
		right.m_size = 0;

		return *this;
	}

	~CMyStack()
	{
		Clear();
	};

private:
	std::shared_ptr<MyNode> m_top = nullptr;
	std::size_t m_size = 0;
};