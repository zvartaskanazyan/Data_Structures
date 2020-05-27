#include "list.h"
#include <iostream>

using std::cout;
using std::endl;


int main()
{
	DoublyLinkedList<int>  list1;

	for (int i = 0; i < 15; ++i) {
		list1.push_front(rand() % 40);
	}
	cout << "List before push_back : ";
	list1();

	for (int i = 0; i < 6; ++i) {
		dll.push_back(i + 1);
	}
	cout << "List after push_back  : ";
	list1.print();
	list1.pop_front();
	cout << "Deleting first element:   ";
	list1.print();
	list1.pop_back();
	cout << "Deleting last element :   ";
	list1.print();
	cout<<"The size of container is : "<<list1.size() << endl;
	
	cout << "The new size of container is : " << list1.size() << endl;
	DoublyLinkedList<int> list2;

	for (int i = 0; i < 15; ++i) {
		list2.push_front(rand() % 40);
	}
	cout << "List before push_back : ";
	list2.print();
	cout << "The  size of container is : " << list2.size() << endl;
	DoublyLinkedList<int>::Bidirectional_Iterator iterator = list2.Begin();
	++iterator;

	list2.insert(iterator, 7);
	cout << "List after insertion  : "; list2.print();
	cout << "The new size of container is : " << list2.size() << endl;


		
	return 0;
}