#ifndef ___DLLIST__
#define ___DLLIST__

#include "ListInterface.h"
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
struct Node
{
	Node* next;
	Node* prev;
	T value;
	Node(T i = T(), Node *p = nullptr, Node *n = nullptr) :value(i), prev(p), next(n) {}
};

template<typename T>
class DoublyLinkedList:public List
{

public:
	class Bidirectional_Iterator
	{
		private:

			Node<T>* _iterator;

		public:
			friend class DoublyLinkedList<T>;
			Bidirectional_Iterator(Node<T>* itr) :_iterator(itr) {}
			Bidirectional_Iterator() :_iterator(nullptr) {}
			Bidirectional_Iterator(const Bidirectional_Iterator& myitr) : _iterator(myitr._iterator) {}
			~Bidirectional_Iterator() {}

			Bidirectional_Iterator& operator=(Node<T>* pNode)
			{
				this->_iterator = pNode;
				return *this;
			}
			bool operator!=(const Bidirectional_Iterator& other)
			{
				return _iterator != other._iterator;
			}
			Bidirectional_Iterator& operator++()
			{
				if (_iterator)
					_iterator = _iterator->next;
				return *this;
			}
		
			Bidirectional_Iterator operator++(int)
			{
				Bidirectional_Iterator iterator = *this;
				++*this;
				return iterator;

			}
			Bidirectional_Iterator& operator--()
			{
				if (_iterator)
					_iterator = _iterator->prev;
				return *this;
			}
			Bidirectional_Iterator operator--(int)
			{
				Bidirectional_Iterator iterator = *this;
				--*this;
				return iterator;
			}
			T& operator*()
			{
				return _iterator->value;
			}
			T operator->() const
			{
				return _iterator->next->value;
			}

	};

public:

	DoublyLinkedList();
	~DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList(std::initializer_list<T> init_list);
	DoublyLinkedList& operator=(const DoublyLinkedList& otherList);
	
	void push_back(const T& value);
	void push_front(const T& value);
	void pop_back();
	void pop_front();
	void remove(const T& value);
	void print();//helper
	void clear();
	Bidirectional_Iterator insert(const Bidirectional_Iterator& in_after, const T& val);

    size_t size() { return counter; }
	bool empty() { return head = nullptr; }
	T& back() { return tail->value; }
	const T& back() const { return tail->value; }
    T& front() { return head->value; }
	const T& front() const { return head->value; }
	
	Bidirectional_Iterator Begin()
	{
		return Bidirectional_Iterator(head);
	}
	const Bidirectional_Iterator Begin() const
	{
		return Bidirectional_Iterator(head);
	}
	Bidirectional_Iterator End()
	{
		return Bidirectional_Iterator(tail);
	}
	const Bidirectional_Iterator End() const
	{
		return Bidirectional_Iterator(tail);
	}
	   
private:
	Node<T>* head;
	Node<T>* tail;
	size_t counter;
};


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	this->head = nullptr;
	this->tail = nullptr;
	this->counter = 0;

}
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node<T>* tmp = nullptr;
	while (head)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}
	head = tail = nullptr;

}
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList & other)
{
	DoublyLinkedList<T> temp(other);
	std::swap(temp.head, head);
	return *this;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> init_list)
{
	for (auto const& value : init_list)
	{
		push_back(value);
	}

}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList & other)
{
	other.std::swap(*this);
	return *this;
}

template<typename T>
void DoublyLinkedList<T>::clear()
{
	Node<T> *curr = head;
	while (curr != nullptr)
	{
		Node<T> *del = curr;
		curr = curr->next;
		delete del;
	}
	--counter;
	head = tail = nullptr;
}


template<typename T>
void DoublyLinkedList<T>::push_back(const T& v)
{
	if (head == nullptr) {
		head = tail = new Node<T>(v);
		tail->value = v;
		++counter;
	}
	else {
		Node<T>* pnode = new Node<T>(v);
		pnode->value = v;
		pnode->next = nullptr;
		pnode->prev = tail;
		tail->next = pnode;
		tail = pnode;
		++counter;
	}
}

template<typename T>
void DoublyLinkedList<T>::push_front(const T& vb) {
	if (head == nullptr) {
		head = tail = new Node<T>(vb);
		head->value = vb;
		++counter;
	}
	else {
		Node<T>* val = new Node<T>(vb);
		head->value = vb;
		head->prev = val;
		val->next = head;
		head = val;
		++counter;
	}
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
	Node<T>* temp = head;
	head = temp->next;
	delete temp;
	--counter;
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
	Node<T>* temper = tail;
	tail = temper->prev;
	tail->next = nullptr;
	delete temper;
	--counter;
}


template<typename T>
typename DoublyLinkedList<T>::Bidirectional_Iterator DoublyLinkedList<T>::insert(const DoublyLinkedList<T>::Bidirectional_Iterator& in_after, const T& val)
{
	Node<T>* node = new Node<T>(val, in_after._iterator, in_after._iterator->next);
	in_after._iterator->next->prev = node;
	in_after._iterator->next = node;
	++counter;
	return Bidirectional_Iterator(node);
}

template<typename T>
void DoublyLinkedList<T>::remove(const T& value)
{
	Node<T>* temper = head;
	while (temper->next != nullptr)
	{
		if (temper->value = value)
			delete temper;
		--counter;
	}
}

template<typename T>
void DoublyLinkedList<T>::print() {
	Node<T>* temp = head;
	while (temp) {

		cout << temp->value << " ";
		temp = temp->next;
	}
	cout << endl;
}
#endif // ___DLLIST__