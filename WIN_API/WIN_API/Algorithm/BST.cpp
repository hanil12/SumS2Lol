#include "BST.h"

BinarySearchTree::BinarySearchTree()
{
}

BinarySearchTree::~BinarySearchTree()
{
	// TODO : 모든 노드 삭제
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(key);

	if (root == nullptr)
	{
		root = newNode;
		return;
	}

	Node* node = root;
	Node* parent = nullptr;

	// 재귀호출 <-> 반복문
	// 자리찾기, 부모찾기
	while (true)
	{
		if (node == nullptr)
			break;

		parent = node;
		if (key < node->key)
		{
			node = node->leftChild;
		}
		else
		{
			node = node->rightChild;
		}
	}

	newNode->parent = parent;
	if (key < parent->key)
	{
		parent->leftChild = newNode;
	}
	else
	{
		parent->rightChild = newNode;
	}
}

void BinarySearchTree::PrintTree(Node* node)
{
	if (node == nullptr)
		return;

	// 전위순회 : 부모 - 왼쪽자식들 - 오른쪽자식들
	// 중위순회 : 왼쪽 - 부모 - 오른쪽
	// 중위순회 : 왼쪽 - 오른쪽 - 부모

	PrintTree(node->leftChild);
	PrintTree(node->rightChild);
	cout << node->key << endl;
}
