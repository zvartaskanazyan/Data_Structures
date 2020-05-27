#ifndef _NODE_
#define _NODE_

template<typename T>
struct Node
{
	Node* m_next;
	T m_data;
	Node(T data,Node* next):m_data(data),m_next(next){}
};

#endif