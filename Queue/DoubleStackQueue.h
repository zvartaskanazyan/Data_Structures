#pragma once
#include <stack>

template<class T>
class DoubleStackQueue
{
public:
	DoubleStackQueue();

	~DoubleStackQueue();

	void enqueue(const T&);

	T dequeue();

	const T& front();

	bool empty() const;

private:
	std::stack<T> m_first;
	std::stack<T> m_second;
};


template<class T>
DoubleStackQueue<T>::DoubleStackQueue() = default;

template<class T>
DoubleStackQueue<T>::~DoubleStackQueue() = default;

template <class T>
void DoubleStackQueue<T>::enqueue(const T& value)
{
	m_first.push(value);
}

template <class T>
T DoubleStackQueue<T>::dequeue()
{
	if (empty()) {
		throw std::out_of_range{ "empty" };
	}

	auto stack_pop = [](std::stack<int>& stack) {
		const auto val = stack.top();
		stack.pop();
		return val;
	};

	if (!m_second.empty()) {
		return stack_pop(m_second);
	}

	while (!m_first.empty()) {
		m_second.push(stack_pop(m_first));
	}

	return stack_pop(m_second);
}

template <class T>
const T& DoubleStackQueue<T>::front()
{
	if (empty()) {
		throw std::out_of_range{ "empty" };
	}

	auto stack_pop = [](std::stack<int>& stack) {
		const auto val = stack.top();
		stack.pop();
		return val;
	};

	if (!m_second.empty()) {
		return m_second.top();
	}

	while (!m_first.empty()) {
		m_second.push(stack_pop(m_first));
	}

	return m_second.top();
}

template <class T>
bool DoubleStackQueue<T>::empty() const
{
	return (m_second.empty()) && (m_first.empty());
}