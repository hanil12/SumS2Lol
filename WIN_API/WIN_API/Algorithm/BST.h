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
	void PrintTree(Node* root);

	Node* Search(Node* root, int key); // key값을 가지는 노드 반환
	Node* Min(Node* root); // node부터 시작하는 트리에서 가장작은값을 가지는 노드 반환
	Node* Max(Node* root); //   "                      가장큰값    "

	void Delete(Node* node);

	Node* root = nullptr;
private:
	Node* Previous(Node* root); // 매개변수 root보다 한칸 더 작은 얘
	Node* Next(Node* root); // 매개변수 root보다 한칸 더 큰 얘

	void Replace(Node* node1, Node* node2);
};