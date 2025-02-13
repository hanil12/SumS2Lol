#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

#include "BST.h"

// BST
// ����Ž��Ʈ��
// - ���� : logN
// - (key)Ž�� : logN
// - ���� : logN
// 
// �ڰ����� ����Ž��Ʈ��
// - �����Ʈ�� (map)
// - (B-Ʈ�� => DB)
// - AVL

int main()
{
	BinarySearchTree tree;
	tree.Insert(100);
	tree.Insert(50);
	tree.Insert(25);
	tree.Insert(75);
	tree.Insert(150);
	tree.Insert(110);
	tree.Insert(200);
	tree.Insert(99);

	tree.PrintTree(tree.root);


	return 0;
}
