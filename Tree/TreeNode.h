#pragma once
template<typename T>
struct TreeNode
{
	explicit TreeNode(const T& data = T()
		, TreeNode* left = nullptr
		, TreeNode* right = nullptr)
		: data{ data }
		, left{ left }
		, right{ right }
	{

	}

	T data;
	TreeNode* left;
	TreeNode* right;
};