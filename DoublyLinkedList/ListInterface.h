#pragma once

template <typename T>
class List
{
public:
	virtual ~List() {}

	virtual bool empty() const = 0;
	virtual size_t size() const = 0;

	virtual const T& getValue(int pos) const = 0;
	virtual void insert(int pos, const T& el) = 0;
	virtual void erase(int pos) = 0;
	virtual void clear() = 0;
};