#pragma once
#include "TreeNode.h"
#include <iostream>
#include <queue>
#include <stack>


template<typename T>
class Tree
{
public:

	explicit Tree(TreeNode<T>* node);

	void pre_order() const;

	void pre_order_iter() const;

	void in_order() const;

	void in_order_iter() const;

	void post_order() const;
	void level_order() const;

	size_t get_tree_width() const;

	size_t leaf_count() const;


private:

	static void pre_order(TreeNode<T>* node);

	static void pre_order_iter(TreeNode<T>* node);

	static void in_order_iter(TreeNode<T>* node);

	static void in_order(TreeNode<T>* node);

	static void post_order(TreeNode<T>* node);

	static void level_order(TreeNode<T>* node);

	static size_t leaf_count(TreeNode<T>*);

	static size_t get_tree_width(TreeNode<T>*);

	TreeNode<T>* m_root;
};

template <typename T>
void Tree<T>::pre_order_iter(TreeNode<T>* node)
{
	std::stack<TreeNode<T>*> s;
	auto tmp = node;
	while (true)
	{
		while (nullptr != tmp)
		{
			std::cout << tmp->data << " ";

			s.push(tmp);

			tmp = tmp->left;
		}

		if (s.empty())
		{
			break;
		}

		tmp = s.top()->right;
		s.pop();
	}

	std::cout << std::endl;
}

template <typename T>
void Tree<T>::in_order_iter(TreeNode<T>* node)
{
	std::stack<TreeNode<T>*> s;
	auto tmp = node;
	while (true)
	{
		while (nullptr != tmp)
		{
			s.push(tmp);
			tmp = tmp->left;
		}

		if (s.empty())
		{
			break;
		}

		tmp = s.top();
		std::cout << tmp->data << " ";
		tmp = tmp->right;
		s.pop();
	}

	std::cout << std::endl;
}

template <typename T>
void Tree<T>::pre_order_iter() const
{
	if (nullptr == m_root)
	{
		return;
	}

	pre_order_iter(m_root);
}

template <typename T>
Tree<T>::Tree(TreeNode<T>* node)
	: m_root{ node }
{
}

template <typename T>
void Tree<T>::pre_order() const
{
	std::cout << "pre_order : ";

	if (nullptr == m_root)
	{
		return;
	}

	pre_order(m_root);

	std::cout << std::endl;
}

template <typename T>
void Tree<T>::in_order() const
{
	std::cout << "in_order : ";

	if (nullptr == m_root)
	{
		return;
	}

	in_order(m_root);
	std::cout << std::endl;
}

template <typename T>
void Tree<T>::in_order_iter() const
{
	if (nullptr == m_root)
	{
		return;
	}

	in_order_iter(m_root);
}

template <typename T>
void Tree<T>::post_order() const
{
	std::cout << "post_order : ";

	if (nullptr == m_root)
	{
		return;
	}

	post_order(m_root);
	std::cout << std::endl;
}

template <typename T>
void Tree<T>::level_order() const
{
	std::cout << "level_order : ";

	if (nullptr == m_root)
	{
		return;
	}

	level_order(m_root);
	std::cout << std::endl;
}

template <typename T>
size_t Tree<T>::get_tree_width() const
{
	if (nullptr == m_root)
	{
		return 0u;
	}

	return get_tree_width(m_root);
}

template <typename T>
size_t Tree<T>::leaf_count() const
{
	if (nullptr == m_root)
	{
		return 0u;
	}

	return leaf_count(m_root);
}

template <typename T>
void Tree<T>::pre_order(TreeNode<T>* node)
{
	std::cout << node->data << " ";

	if (node->left != nullptr)
	{
		pre_order(node->left);
	}

	if (node->right != nullptr)
	{
		pre_order(node->right);
	}
}

template <typename T>
void Tree<T>::in_order(TreeNode<T>* node)
{
	if (node->left != nullptr)
	{
		in_order(node->left);
	}

	std::cout << node->data << " ";

	if (node->right != nullptr)
	{
		in_order(node->right);
	}
}

template <typename T>
void Tree<T>::post_order(TreeNode<T>* node)
{

	if (node->left != nullptr)
	{
		post_order(node->left);
	}

	if (node->right != nullptr)
	{
		post_order(node->right);
	}

	std::cout << node->data << " ";
}

template <typename T>
void Tree<T>::level_order(TreeNode<T>* node)
{
	std::queue<TreeNode<T>*> q;
	q.push(node);

	while (!q.empty())
	{
		auto item = q.front();
		q.pop();

		std::cout << item->data << " ";

		if (nullptr != item->left)
		{
			q.push(item->left);
		}

		if (nullptr != item->right)
		{
			q.push(item->right);
		}
	}
}

template <typename T>
size_t Tree<T>::leaf_count(TreeNode<T>* node)
{
	if (nullptr == node->left && nullptr == node->right)
	{
		return 1u;
	}

	auto res{ 0u };

	if (nullptr != node->left)
	{
		res += leaf_count(node->left);
	}

	if (nullptr != node->right)
	{
		res += leaf_count(node->right);
	}

	return res;
}

template <typename T>
size_t Tree<T>::get_tree_width(TreeNode<T>* node)
{
	std::queue<TreeNode<T>*> q;
	q.push(node);

	auto max{ 0u };

	while (!q.empty())
	{
		const auto queue_size = q.size();

		max = std::max(max, queue_size);

		for (auto i = 0u; i < queue_size; ++i)
		{
			auto tmp = q.front();
			q.pop();

			if (nullptr != tmp->left)
			{
				q.push(tmp->left);
			}

			if (nullptr != tmp->right)
			{
				q.push(tmp->right);
			}
		}
	}

	return max;
}
