#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdio.h"
#include "math.h"

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode * m_pLeft;
	BinaryTreeNode * m_pRight;
};


BinaryTreeNode * ConstructCore(
	int * startPreorder, int * endPreorder,
	int * startInorder, int * endInorder
)
{
	int rootValue = startPreorder[0];
	BinaryTreeNode * root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = NULL;


	// 只有一个节点
	if (startPreorder == endPreorder)
	{
		// 只有一个节点，为何还要判断
		if (startInorder == endInorder &&
			*startPreorder == *startInorder)
			return root;
	}

	// find root value in inorder array
	int * rootInorder = startInorder;
	while (rootInorder < endInorder && * rootInorder != rootValue)
	{
		++rootInorder;
	}

	if (rootInorder == endInorder && *rootInorder != rootValue)
		throw std::exception("invalid input.");

	// got left node count & right node count
	int leftLength = rootInorder - startInorder;
	int * leftPreorderEnd = startPreorder + leftLength;

	// 递归
	if (leftLength > 0)
	{
		// 第一个是根节点
		root->m_pLeft = ConstructCore(
			startPreorder + 1, leftPreorderEnd,
			startInorder, rootInorder - 1);
	}

	if (leftLength < endPreorder - startPreorder)
	{
		root->m_pRight = ConstructCore(
			leftPreorderEnd + 1, endPreorder,
			rootInorder + 1, endInorder
		);
	}

	return root;
}


BinaryTreeNode * Construct(int * preorder, int * inorder, int length)
{
	if (preorder == NULL || inorder == NULL || length <= 0)
		return NULL;

	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}


static int test()
{
	clock_t t = clock();
	int * A = new int[8]{ 1,2,4,7,3,5,6,8 };
	int * B = new int[8]{ 4,7,2,1,5,3,8,6 };

	auto root = Construct(A,B,8);


	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
