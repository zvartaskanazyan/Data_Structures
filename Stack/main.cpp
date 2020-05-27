#include"pch.h"
#include <iostream>
#include "LStack.h"
#include "AStack.h"
using std::cout;
using std::endl;
int function(const int& k)
{
	return  k ;
}
int main()
{
	LStack<int> Lstack;
	for (size_t i = 0; i < 15; ++i)
	{
		Lstack.push(i);
	}

	Lstack.print();
	Lstack.clean();
	Lstack.print();
	//cout << Lstack.top() << endl;
	cout << endl << endl;
	cout << "*****************************" << endl;
	AStack<int> Astack;
	for (size_t i = 0; i < 25; ++i)
	{
		Astack.push(i);
	}
	Astack.print();

	cout << "The top of stack before poping is : " << Astack.top() << endl << endl;

	cout<< "The poping element of stack is : " << Astack.pop() << endl << endl;
	Astack.print(); 
	cout <<"The top of stack after poping is : " << Astack.top() << endl << endl;
	Astack.clean(); Astack.print();

	return 0;
}