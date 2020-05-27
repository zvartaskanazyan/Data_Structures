#ifndef _LSTACK_
#define _LSTACK_
#include "Stack.h"
#include "Node.h"
#include "assert.h"

template <typename T>
class LStack :public Stack<T>
{
public:
	LStack(size_t size, Node<T>* top = nullptr) 
		      :m_size(size)
		      ,m_top(top) {}
	LStack()
	{
		 m_size = 0;
		 m_top = nullptr;
	}
	~LStack() 
	{
		clean();
	}
	virtual void push(const T& value) 
	{
		m_top = new Node<T>(value, m_top);
		++m_size;
	}
	virtual T pop()
	{
		assert(!empty());
		const T val = top();
		Node<T>* top = m_top;
		m_top = m_top->m_next;
		delete top;
		--m_size;
		return val;

	}
	virtual bool empty() const
	{
		return nullptr == m_top;
	}
	virtual void clean()
	{
		while (!empty())
			pop();

	}
	virtual const T& top() const
	{
		assert(!empty());
		return m_top->m_data;
	}
	virtual size_t size() const
	{
		return m_size;
	}
	virtual void print()
	{
		Node<T>* ptr = nullptr;
		if (m_top == nullptr)
			std::cout << "Stack is empty";
		else {
			ptr = m_top;
			std::cout << "First Stack elements are: ";
			while (ptr != nullptr) {
				std::cout << ptr->m_data << " ";
				ptr = ptr->m_next;
			}
		}
		std::cout << std::endl;
	}
private:
	Node<T>* m_top;
	size_t m_size;
};


#endif