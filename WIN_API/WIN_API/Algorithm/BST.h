#pragma once

#include <iostream>

using namespace std;

struct Node
{
	Node() {}
	Node(int key) { this->key = key; }

	int data = 0;
	int key = -1;

	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	Node* parent = nullptr;
};

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void Insert(int key);
	void PrintTree(Node* node);

	Node* Search(Node* node, int key); // key���� ������ ��� ��ȯ
	Node* Min(Node* node); // node���� �����ϴ� Ʈ������ ������������ ������ ��� ��ȯ
	Node* Max(Node* node); //   "                      ����ū��    "

	Node* Previous(Node* node); // �Ű����� node���� ��ĭ �� ���� ��
	Node* Next(Node* node); // �Ű����� node���� ��ĭ �� ū ��

	Node* root = nullptr;
};