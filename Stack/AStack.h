#ifndef _ASTACK_
#define _ASTACK_
#include "Stack.h"
#include "assert.h"

const size_t MAX_SIZE = 50;

template <typename T>
class AStack :public Stack<T>
{
public:
	AStack():m_top(0)
	{	

	}
	~AStack()
	{
		
	}
	virtual void push(const T& value)
	{
		assert(!(m_top == MAX_SIZE));
        ++m_top;
		m_stack[m_top] = value;
		
	}
	virtual T pop()
	{
		assert(!empty());
		T temp = m_stack[m_top];
		--m_top;
		return temp; 
		
	}
	virtual bool empty() const
	{
		return  m_top == 0 ;
	}
	virtual void clean()
	{
		while (!empty())
			pop();

	}
	virtual const T& top() const
	{
		assert(!empty());
		return m_stack[m_top];
	}
	virtual size_t size() const
	{
		return m_top;
	}
	virtual void print()
	{
		if (m_top == 0)
			std::cout << "Stack is empty" << std::endl;
		else {

			std::cout << "Second Stack elements are : ";
			for (int i = m_top; i > 0; --i)
			{
				std::cout << m_stack[i] << " ";
			}
			std::cout << std::endl;
		}
	}
private:
	T m_stack[MAX_SIZE];
	size_t m_top;
};
#endif // !_ASTACK_
