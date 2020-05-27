#pragma once
#include "pch.h"
#include "base_queue.h"
#include <cassert>

template<class T>
class AQueue final : public Queue<T>
{
public:
	explicit AQueue(const size_t size);

	void enqueue(const T& value) override;

	T dequeue() override;

	const T& front() override;

	bool full() const override;

	bool empty() const override;

	void clear() override;

	size_t length() const override;

	~AQueue() override;

private:
	size_t m_max_size;
	T* m_array;
	size_t m_front;
	size_t m_rear;
};

template <class T>
AQueue<T>::AQueue(const size_t size)
	: m_max_size(size + 1)
	, m_array(new T[m_max_size])
	, m_front(1)
	, m_rear(0)
{
	assert(nullptr != m_array);
}

template <class T>
void AQueue<T>::enqueue(const T& value)
{
	assert(!full());
	m_rear = (m_rear + 1) % m_max_size;
	m_array[m_rear] = value;
}

template <class T>
T AQueue<T>::dequeue()
{
	assert(!empty());
	const T& tmp = m_array[m_front];
	m_front = (m_front + 1) % m_max_size;
	return tmp;
}

template <class T>
const T& AQueue<T>::front()
{
	assert(!empty());
	return m_array[m_front];
}

template <class T>
bool AQueue<T>::full() const
{
	return ((m_rear + 1) % m_max_size == m_front - 1);
}

template <class T>
bool AQueue<T>::empty() const
{
	return length() == 0;
}

template <class T>
void AQueue<T>::clear()
{
	while (!empty()) {
		dequeue();
	}
}

template <class T>
size_t AQueue<T>::length() const
{
	return (m_rear - m_front + 1 + m_max_size) % m_max_size;
}

template <class T>
AQueue<T>::~AQueue()
{
	delete[] m_array;
	m_array = nullptr;
}

