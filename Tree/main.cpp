#include "pch.h"
#include<iostream>
#include"Tree.h"


int main(int argc, char* argv[])
{
	/*TreeNode<char>* g = new TreeNode<char>('G');
	TreeNode<char>* h = new TreeNode<char>('H');
	TreeNode<char>* f = new TreeNode<char>('F', g, h);
	TreeNode<char>* e = new TreeNode<char>('E');
	TreeNode<char>* c = new TreeNode<char>('C', e, f);
	TreeNode<char>* d = new TreeNode<char>('D');
	TreeNode<char>* b = new TreeNode<char>('B', nullptr, d);
	TreeNode<char>* a = new TreeNode<char>('A', b, c);

	Tree<char> tree{ a };*/

	TreeNode<int>* g = new TreeNode<int>(7,nullptr, nullptr);
	TreeNode<int>* h = new TreeNode<int>(9, nullptr, nullptr);
	TreeNode<int>* f = new TreeNode<int>(3, nullptr, nullptr);
	TreeNode<int>* e = new TreeNode<int>(0,nullptr,f);
	TreeNode<int>* c = new TreeNode<int>(8,g,h);
	TreeNode<int>* d = new TreeNode<int>(-11,nullptr,nullptr);
	TreeNode<int>* b = new TreeNode<int>(-1,d,e);
	TreeNode<int>* a = new TreeNode<int>(5, b, c);

	Tree<int> tree{ a };

	tree.pre_order();
	tree.pre_order_iter();
	tree.in_order();
	tree.in_order_iter();
	tree.post_order();
	tree.level_order();

	std::cout << "tree width : " << tree.get_tree_width() << std::endl;

	std::cout << "tree leafs count : " << tree.leaf_count() << std::endl;

	return 0;
}
