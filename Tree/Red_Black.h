#pragma once
#include <iostream>
#include <algorithm>
#include <cassert>
using std::cout;
using std::endl;

template <class T>
class RedBlackTree 
{
	enum Color { Red, Black };
	struct Node
	{
		T	  info_;
		Node* llink_;
		Node* rlink_;
		Node* parent_;
		Color color_;
		Node(T info = T(), Node* llink = 0, Node* rlink = 0, Node* parent = 0, Color color = Red)
			: info_(info), llink_(llink), rlink_(rlink),parent_(parent),color_(color)
		{}
	};

	//private methods
private:
	static void   clear(Node*& tree);
	static bool   find(const Node* tree, const T& elem); 
	static Node*  insert(Node*& root, Node*& ptr);
	static Node*  remove(Node*& tree, const T& elem);
	static Node*  minValue(Node*& node);
	static Node*  maxValue(Node*& node);
	size_t        height(Node* root);
	void	PrintPreorder(Node* ptr)const;
	void	PrintInorder(Node* ptr)const;
	void  	PrintPostorder(Node* ptr)const;

	//private member variables
private:
	Node* 	root_;
	size_t	size_;

	//Public methods
public:
	RedBlackTree();
	RedBlackTree(const RedBlackTree& other);
	RedBlackTree& operator=(const RedBlackTree& other);
	~RedBlackTree();

	//Some move related staff
	RedBlackTree(RedBlackTree&& other);
	RedBlackTree& operator=(const RedBlackTree&& other);

	//Accessors
	bool   	empty()const;
	size_t	size()const;
	bool  	find(const T& elem)const;
	void	PrintInorder()const; 
	void	PrintPreorder()const; 
	void	PrintPostorder()const;
	size_t  height();
	int     getColor(Node*& node);
	void    setColor(Node*& node, Color color);

	void    InsertFixUp(Node *&ptr);
	void    DeleteFixUp(Node*& node);
	void    LeftRotate(Node *&ptr);
	void    RightRotate(Node *&ptr);
	void	insert(const T& elem);
	void	remove(const T& elem);
	void	clear();

	struct iterator {
	};

	iterator begin() { return iterator{ root_ }; }
	iterator end() { return {}; }

};

template<class T>
RedBlackTree<T>::RedBlackTree() :root_(nullptr), size_(0)
{
}

template<class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree& other)
{
	other.copy(root_);
}

template<class T>
inline RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree& other)
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
RedBlackTree<T>::~RedBlackTree()
{
	clear(root_);
}

template<class T>
inline RedBlackTree<T>::RedBlackTree(RedBlackTree&& other)
{
	root_ = std::move(other.root_);
	other.root_ = nullptr;
}

template<class T>
inline RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree&& other)
{
	std::swap(root_, other.root_);
	std::swap(size_, other.size_);
	return *this;
}

template<class T>
inline void RedBlackTree<T>::clear(Node*& tree)
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
inline bool RedBlackTree<T>::find(const Node* tree, const T& elem)
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
inline typename RedBlackTree<T>::Node* RedBlackTree<T>::insert(Node *&root, Node *&ptr)
{
	if (root == nullptr)
		return ptr;

	if (ptr->info_ < root->info_) {
		root->llink_ = insert(root->llink_, ptr);
		root->llink_->parent_ = root;
	}
	else if (ptr->info_ > root->info_) {
		root->rlink_ = insert(root->rlink_, ptr);
		root->rlink_->parent_ = root;
	}

	return root;
}

template<class T>
inline typename  RedBlackTree<T>::Node* RedBlackTree<T>::remove(Node*& tree, const T& elem)
{
	if (tree == nullptr) return tree;

	if (elem < tree->info_)
	{
		return remove(tree->llink_, elem);
	}

	if (elem > tree->info_)
	{
		return remove(tree->rlink_, elem);
	}

	if (tree->llink_ == nullptr || tree->rlink_ == nullptr)
		return tree;

	Node *temp = minValue(tree->rlink_);
	tree->info_ = temp->info_;
	return remove(tree->rlink_, temp->info_);
	
}

template<class T>
inline void RedBlackTree<T>::PrintInorder(Node *ptr) const
{
	if (ptr->llink_ != nullptr)
	{
		PrintInorder(ptr->llink_);
	}

	cout << ptr->info_ << " " << ptr->color_ << endl;

	if (ptr->rlink_ != nullptr)
	{
		PrintInorder(ptr->rlink_);
	}
}

template<class T>
inline void RedBlackTree<T>::PrintPreorder(Node* ptr)const
{
	cout << ptr->info_ << " " << ptr->color_ << endl;

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
inline void RedBlackTree<T>::PrintPostorder(Node *ptr) const
{
	if (ptr->llink_ != nullptr)
	{
		PrintPostorder(ptr->llink_);
	}

	if (ptr->rlink_ != nullptr)
	{
		PrintPostorder(ptr->rlink_);
	}

	cout << ptr->info_ << " " << ptr->color_ << endl;
}

template<class T>
inline bool RedBlackTree<T>::empty()const
{
	return (root_ == 0);
}

template<class T>
inline size_t RedBlackTree<T>::size()const
{
	return size_;
}

template<class T>
inline bool RedBlackTree<T>::find(const T& elem)const
{
	return find(root_, elem);
}

template<class T>
inline void RedBlackTree<T>::PrintInorder()const
{
	if (nullptr == root_)
	{
		return;
	}

	PrintInorder(root_);
	std::cout << std::endl;
}

template<class T>
inline void RedBlackTree<T>::PrintPreorder() const
{
	if (nullptr == root_)
	{
		return;
	}

	PrintPreorder(root_);
	std::cout << std::endl;
}

template<class T>
inline void RedBlackTree<T>::PrintPostorder()const
{
	if (nullptr == root_)
	{
		return;
	}

	PrintPostorder(root_);
	std::cout << std::endl;
}

template<class T>
inline size_t RedBlackTree<T>::height()
{
	return height(this->root_);
}

template<class T>
inline int RedBlackTree<T>::getColor(Node *& node)
{
	if (node == nullptr)
		return Black;

	return node->color_;
}

template<class T>
inline void RedBlackTree<T>::setColor(Node*& node, Color color)
{
	if (node == nullptr)
		return;

	node->color_ = color;
}

template<class T>
inline typename RedBlackTree<T>::Node* RedBlackTree<T>::minValue(Node *&node) {

	Node *ptr = node;
	while (ptr->llink_ != nullptr)
	{
		ptr = ptr->llink_;
	}
		return ptr;
}

template<class T>
inline typename RedBlackTree<T>::Node* RedBlackTree<T>::maxValue(Node *&node) 
{
	Node *ptr = node;

	while (ptr->rlink_ != nullptr)
	{
		ptr = ptr->rlink_;
	}
	return ptr;
}

template<class T>
bool RedBlackTree<T>::find(const T& elem)const
{
	return find(root_, elem);
}


template<class T>
inline size_t RedBlackTree<T>::height(Node* root)
{
	if (root == nullptr)
		return 0;
	else
	{
		size_t left = height(root ->llink_);
		size_t right = height(root ->rlink_);
		return (std::max(left, right) + 1);
	}
}

template<class T>
inline void RedBlackTree<T>::InsertFixUp(Node*& ptr)
{ 
	Node *parent = nullptr;
	while (ptr != root_ && getColor(ptr) == Red && getColor(ptr->parent_) == Red) {
		parent = ptr->parent_;
		parent->parent_ = parent->parent_;
		if (parent == parent->parent_->llink_) {
			Node *Ptr = parent->parent_->rlink_;
			if (getColor(Ptr) == Red) {
				setColor(Ptr, Black);
				setColor(parent, Black);
				setColor(parent->parent_, Red);
				ptr = parent->parent_;
			}
			else {
				if (ptr == parent->rlink_) {
					LeftRotate(parent);
					ptr = parent;
					parent = ptr->parent_;
				}
				RightRotate(parent->parent_);
				std::swap(parent->color_, parent->parent_->color_);
				ptr = parent;
			}
		}
		else {
			Node *Ptr = parent->parent_->llink_;
			if (getColor(Ptr) == Red) {
				setColor(Ptr, Black);
				setColor(parent, Black);
				setColor(parent->parent_, Red);
				ptr = parent->parent_;
			}
			else {
				if (ptr == parent->llink_) {
					RightRotate(parent);
					ptr = parent;
					parent = ptr->parent_;
				}
				LeftRotate(parent->parent_);
				std::swap(parent->color_, parent->parent_->color_);
				ptr = parent;
			}
		}
	}
	setColor(root_, Black);
}

template<class T>
inline void RedBlackTree<T>::DeleteFixUp(Node*& node)
{
	if (node == nullptr)
		return;

	if (node == root_) {
		root_ = nullptr;
		return;
	}

	if (getColor(node) == Red || getColor(node->llink_) == Red || getColor(node->rlink_) == Red) 
	{
		Node *child = node->llink_ != nullptr ? node->llink_ : node->rlink_;

		if (node == node->parent_->llink_) {
			node->parent_->llink_ = child;
			if (child != nullptr)
				child->parent_ = node->parent_;
			setColor(child, Black);
			delete (node);
		}
		else {
			node->parent_->rlink_ = child;
			if (child != nullptr)
				child->parent_ = node->parent_;
			setColor(child, Black);
			delete (node);
		}
	}
	else {
		Node *sibling = nullptr;
		Node *parent = nullptr;
		Node *ptr = node;
		setColor(ptr, Black);
		while (ptr != root_ && getColor(ptr) == Black) {
			parent = ptr->parent_;
			if (ptr == parent->llink_) {
				sibling = parent->rlink_;
				if (getColor(sibling) == Red) {
					setColor(sibling, Black);
					setColor(parent, Red);
					LeftRotate(parent);
				}
				else {
					if (getColor(sibling->llink_) == Black && getColor(sibling->rlink_) == Black) {
						setColor(sibling, Red);
						if (getColor(parent) == Red)
							setColor(parent, Black);
						else
							setColor(parent, Black);
						ptr = parent;
					}
					else {
						if (getColor(sibling->rlink_) == Black) {
							setColor(sibling->llink_, Black);
							setColor(sibling, Red);
							RightRotate(sibling);
							sibling = parent->rlink_;
						}
						setColor(sibling, parent->color_);
						setColor(parent, Black);
						setColor(sibling->rlink_, Black);
						LeftRotate(parent);
						break;
					}
				}
			}
			else {
				sibling = parent->llink_;
				if (getColor(sibling) == Red) {
					setColor(sibling, Black);
					setColor(parent, Red);
					RightRotate(parent);
				}
				else {
					if (getColor(sibling->llink_) == Black && getColor(sibling->rlink_) == Black) {
						setColor(sibling, Red);
						if (getColor(parent) == Red)
							setColor(parent, Black);
						else
							setColor(parent, Black);
						ptr = parent;
					}
					else {
						if (getColor(sibling->llink_) == Black) {
							setColor(sibling->rlink_, Black);
							setColor(sibling, Red);
							LeftRotate(sibling);
							sibling = parent->llink_;
						}
						setColor(sibling, parent->color_);
						setColor(parent, Black);
						setColor(sibling->llink_, Black);
						RightRotate(parent);
						break;
					}
				}
			}
		}
		if (node == node->parent_->llink_)
			node->parent_->llink_ = nullptr;
		else
			node->parent_->rlink_ = nullptr;
		delete(node);
		setColor(root_, Black);
	}

}

template<class T>
inline void RedBlackTree<T>::LeftRotate(Node*& ptr)
{
	Node *rlink_child = ptr->rlink_;
	ptr->rlink_ = rlink_child->llink_;

	if (rlink_child->llink_ != nullptr)
		rlink_child->llink_->parent_ = ptr;

	rlink_child->parent_ = ptr->parent_;

	if (ptr->parent_ == nullptr)
		root_ = rlink_child;
	else if (ptr == ptr->parent_->llink_)
		ptr->parent_->llink_ = rlink_child;
	else
		ptr->parent_->rlink_ = rlink_child;

	rlink_child->llink_ = ptr;
	ptr->parent_ = rlink_child;
}

template<class T>
inline void RedBlackTree<T>::RightRotate(Node*& ptr)
{
	Node *llink_child = ptr->llink_;
	ptr->llink_ = llink_child->rlink_;

	if (ptr->llink_ != nullptr)
		ptr->llink_->parent_ = ptr;

	llink_child->parent_ = ptr->parent_;

	if (ptr->parent_ == nullptr)
		root_ = llink_child;
	else if (ptr == ptr->parent_->rlink_)
		ptr->parent_->rlink_ = llink_child;
	else
		ptr->parent_->llink_ = llink_child;

	llink_child->rlink_ = ptr;
	ptr->parent_ = llink_child;
}

template<class T>
inline void RedBlackTree<T>::insert(const T& elem)
{
	Node *node = new Node(elem);
	root_ = insert(root_, node);
	InsertFixUp(node);
	++size_;

}

template<class T>
inline void RedBlackTree<T>::remove(const T& elem)
{
	Node *node = remove(root_, elem);
	DeleteFixUp(node);
		--size_;
}

template<class T>
inline void RedBlackTree<T>::clear()
{
	while (root_ != 0)
	{
		clear(root_);
	}
}