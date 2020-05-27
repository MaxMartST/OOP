#pragma once
#include <cstddef>

template <typename T>
class CMyStack
{
public:
	CMyStack() = default;
	
	CMyStack(const CMyStack& other)
	{
		*this = other;
	};

	CMyStack(CMyStack&& other)
		: m_top(other.m_top)
		, m_size(other.m_size)
	{
		other.m_top = nullptr;
		other.m_size = 0;
	};

	void Push(const T& element)
	{
		m_top = std::make_shared<Node>(element, m_top);
		++m_size;
	};

	void Pop()
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}

		m_top = m_top->next;
		--m_size;
	};

	bool IsEmpty() const
	{
		return !m_top;
	};

	T GetElement() const
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}
		return m_top->value;
	};

	std::size_t GetSize() const
	{
		return m_size;
	}

	void Clear()
	{
		while (m_top != nullptr)
		{
			m_top = m_top->next;
		}
	};

	~CMyStack()
	{
		Clear();
	};

private:
	struct MyNode
	{
		Node(const T& value, const std::shared_ptr<Node>& next = nullptr)
			: value(value)
			, next(next)
		{};

		T value;
		std::shared_ptr<Node> next;
	};

	std::shared_ptr<MyNode> m_top = nullptr;
	std::size_t m_size = 0;
};
