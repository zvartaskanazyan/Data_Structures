#pragma once
#include <iostream>
using std::cout;
using std::endl;

template <class T>
class SearchTree {

	struct Node {
		T		info_;
		Node*	llink_;
		Node*	rlink_;
		Node(T info = T(), Node* llink = 0, Node* rlink = 0)
			: info_(info), llink_(llink), rlink_(rlink)
		{}
	};

	//Static methods
	static Node*  copy(const Node* tree);
	static void   clear(Node*& tree);
	static void   print(const Node* tree, int indent);
	
	static bool   find(const Node* tree, const T& elem);
	static bool   insert(Node*& tree, const T& elem);
	static bool	  remove(Node*& tree, const T& elem); 

	//Service methods
	void	PrintPreorder(Node* ptr)const;
	void	PrintInorder(Node* ptr)const;
	void  	PrintPostorder(Node* ptr)const;

	//Member variables
private:
	Node* 	root_;
	size_t	size_;

	//Public methods
public:
	SearchTree();
	SearchTree(const SearchTree& other);

	~SearchTree();

	SearchTree& operator=(const SearchTree& other);

	//Some move related staff
	SearchTree(SearchTree&& other);
	SearchTree& operator=(const SearchTree&& other);

	//Accessors
	bool   	empty()const;
	size_t	size()const;
	bool  	find(const T& elem)const;
	void   	print()const;
	void	PrintInorder()const;
	void	PrintPreorder()const;
	void	PrintPostorder()const;

	//Iterators
	struct iterator {
	};

	iterator begin() { return iterator{ root_ }; }
	iterator end() { return {}; }

	//Modifiers
	void	emplace(T&& elem);
	void	insert(const T& elem);
	void	remove(const T& elem);
	void	clear();
};

////////////////////////////////////////////////////////////////////////
//	   		      _____ IMPLEMENTATION _____                          //
////////////////////////////////////////////////////////////////////////

//_____ STATIC METHODS _____
template<class T>
typename SearchTree<T>::Node* SearchTree<T>::copy(const Node* tree)
{
	// if tree is empty
	if (tree == 0) {
		// we are done
		return 0;
	}

	// construct copy of the root with
	return new Node(
		tree->info_,
		copy(tree->llink_), // left subtree copied
		copy(tree->rlink_)  // and right one
	);
}

template<class T>
void SearchTree<T>::clear(Node*& tree)
{
	// if tree is empty
	if (tree == 0) {
		// we are done
		return;
	}

	// clear left
	clear(tree->llink_);
	// clear left
	clear(tree->rlink_);
	// delete root
	delete tree;
	// mark tree empty
	tree = 0;
}

template<class T>
void SearchTree<T>::print(const Node* tree, int indent)
{
	// if tree is empty
	if (tree == 0) {
		// we are done
		return;
	}
	// some magic margin
	enum { margin = 5 };

	// print right with some indent plus margin
	print(tree->rlink_, indent + margin);

	// emulate indentation	
	for (int i = 0; i < indent; ++i) cout << ' ';
	// print root
	cout <<  tree->info_ << endl;

	// print left subtree
	print(tree->llink_, indent + margin);
}

template<class T>
bool SearchTree<T>::find(const Node* tree, const T& elem)
{
	// if tree is empty 
	if (tree == 0) {
		// tree doesn't contain elem for sure 
		return 0;
	}
	// if elem is equal to root element 
	if (tree->info_ == elem) {
		// say we are lucky
		return true;
	}

	// if elem compares less than root element
	if (elem < tree->info_) {
		// it must be in left subtree
		return find(tree->llink_, elem);
	}

	// last hope is right subtree
	return find(tree->rlink_, elem);
}

template<class T> 
bool SearchTree<T>::insert(Node*& tree, const T& elem)
{
	if (tree == 0)
	{		
	  tree = new Node(elem);
      return true;
	}

	//the element is already exist
	if (tree->info_ == elem) {
			return false;
	}
	else
	{
		if (elem < tree->info_)
		{
			if (tree->llink_ == nullptr)
				tree->llink_ = new Node(elem, tree->llink_);
			else
				insert(tree->llink_, elem);

			return true;
		}
		

		if (elem > tree->info_)
		{
			if (tree->rlink_ == nullptr)
				tree->rlink_ = new Node(elem, tree->rlink_);
			else
				insert(tree->rlink_, elem);
			return true;
		}
		
	}
	return false;
}

template<class T>
bool SearchTree<T>::remove(Node*& tree, const T& elem)
{
	if (tree == 0) return false;

	if (elem < tree->info_)
	{
		 remove(tree->llink_, elem);
          return true;
	}
	
	if (elem > tree->info_)
	{
		 remove(tree->rlink_, elem);
		
		return true;
	}
	else
	{
		if (tree->llink_ == nullptr && tree->rlink_ == nullptr)
		{
			delete tree;
			tree = nullptr;
		}
		else if (tree->llink_ == nullptr)
		{
			Node* temp = tree->rlink_;
			tree = tree->rlink_;
			delete temp;
			return true;
		}
		else if (tree->rlink_ == nullptr)
		{
			Node* temp = tree->llink_;
			tree = tree->llink_;
			delete temp;
			return true;
		}
	}
	return false;
}

//_______SERVICE METHODS_______

template<class T>
void SearchTree<T>::PrintInorder(Node *ptr) const
{
	if (ptr->llink_ != nullptr)
	{
		PrintInorder(ptr->llink_);
   	}
	
    cout << ptr->info_ << " ";

	if (ptr->rlink_ != nullptr)
	{
		PrintInorder(ptr->rlink_);
	}
	

}

template<class T>
void SearchTree<T>::PrintPreorder(Node* ptr)const
{
   	cout << ptr->info_ << " ";

	if (ptr->llink_ != nullptr)
	{
		PrintPreorder(ptr->llink_);
	}
	
	if (ptr->rlink_ != nullptr)
	{
		PrintPreorder(ptr->rlink_);
	}
}

template<class T>
void SearchTree<T>::PrintPostorder(Node *ptr) const
{
	if (ptr->llink_ != nullptr)
	{
		PrintPostorder(ptr->llink_);
	}

	if (ptr->rlink_ != nullptr)
	{
		PrintPostorder(ptr->rlink_);
	}
	
	cout << ptr->info_ << " ";
}

//______ PUBLIC METHODS ______
template<class T>
SearchTree<T>::SearchTree():root_(nullptr),size_(0)
{
}

template<class T>
SearchTree<T>::SearchTree(const SearchTree& other) 
{
	other.copy(root_);
}

template<class T>
SearchTree<T>::SearchTree(SearchTree&& other)
{
	root_ = std::move(other.root_);
	other.root_ = nullptr;
}

template<class T>
SearchTree<T>& SearchTree<T>::operator=(const SearchTree& other)
{
	if (this != &other)
	{
		if (root_ != nullptr)  

			clear(root_);

		if (other.root_ == nullptr) 
			root_ = nullptr;
		else
			copy(other.root_);
	}
     	return *this;
}

template<class T>
SearchTree<T>& SearchTree<T>::operator=(const SearchTree&& other)
{
	std::swap(root_, other.root_);
	std::swap(size_, other.size_);
	return *this;
}

template<class T>
SearchTree<T>::~SearchTree()
{
	clear(root_);
}

template<class T>
bool SearchTree<T>::empty()const
{
	return (root_ == 0);
}

template<class T>
size_t SearchTree<T>::size()const
{
	return size_;
}

template<class T>
bool SearchTree<T>::find(const T& elem)const
{
	return find(root_, elem);
}

template<class T>
void SearchTree<T>::PrintInorder()const
{
	if (nullptr == root_)
	{
		return;
	}

	PrintInorder(root_);
	std::cout << std::endl;
}

template<class T>
void SearchTree<T>::PrintPreorder() const
{
	if (nullptr == root_)
	{
		return;
	}

	PrintPreorder(root_);
	std::cout << std::endl;
}

template<class T>
void SearchTree<T>::PrintPostorder()const
{
	if (nullptr == root_)
	{
		return;
	}

	PrintPostorder(root_);
	std::cout << std::endl;
}

template<class T>
void SearchTree<T>::insert(const T& elem)
{
	if (insert(root_, elem))
		++size_;
}

template<class T>
void SearchTree<T>::remove(const T& elem)
{
	if (remove(root_, elem))
		--size_;
}

template<class T>
void SearchTree<T>::print()const
{
	if (root_ != nullptr)
	print(root_, root_->info_);
}

template<class T>
void SearchTree<T>::clear()
{
	while (root_ != 0)
	{
		clear(root_);
	}
}