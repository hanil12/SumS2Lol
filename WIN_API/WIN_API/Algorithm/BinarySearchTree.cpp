#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

#include "BST.h"

// BST
// 이진탐색트리
// - 삽입 : logN
// - (key)탐색 : logN
// - 삭제 : logN
// 
// 자가균형 이진탐색트리
// - 레드블랙트리 (map)
// - (B-트리 => DB)
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
