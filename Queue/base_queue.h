#pragma once

template<class T>
class Queue
{
public:

	virtual void enqueue(const T&) = 0;
	virtual T dequeue() = 0;
	virtual const T& front() = 0;
	virtual bool full() const = 0;
	virtual bool empty() const = 0;
	virtual void clear() = 0;
	virtual size_t length() const = 0;
	virtual ~Queue()
	{
	}
};