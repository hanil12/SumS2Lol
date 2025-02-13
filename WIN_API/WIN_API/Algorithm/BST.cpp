#include "BST.h"

BinarySearchTree::BinarySearchTree()
{
}

BinarySearchTree::~BinarySearchTree()
{
	// TODO : ��� ��� ����
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

	// ���ȣ�� <-> �ݺ���
	// �ڸ�ã��, �θ�ã��
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

	// ������ȸ : �θ� - �����ڽĵ� - �������ڽĵ�
	// ������ȸ : ���� - �θ� - ������
	// ������ȸ : ���� - ������ - �θ�

	PrintTree(node->leftChild);
	PrintTree(node->rightChild);
	cout << node->key << endl;
}
