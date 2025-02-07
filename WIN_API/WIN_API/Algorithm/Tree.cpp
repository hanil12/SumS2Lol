#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

// 트리
// 1. 계층적 구조를 나타내는 자료구조(부모와 자식관계)
// 2. 트리는 잘라도 트리다. (서브트리의 존재)
// => 트리는 재귀적 속성을 갖는다.

// 트리의 종류
// 1. 이진트리
// 2. 포화이진트리
// 3. 완전이진트리
// 4. 힙트리 (priority queue)
// 5. (자가균형)이진탐색트리 (map, 레드블랙트리)

struct Node
{
	string data;

	vector<Node*> children;
};

Node* CreateTree()
{
	// C 스타일
	Node* root = new Node();
	root->data = "개발팀";
	
	// 프로그래밍 팀
	Node* programming = new Node();
	programming->data = "프로그래밍팀";
	root->children.push_back(programming);
	{
		Node* node1 = new Node();
		node1->data = "클라이언트";
		programming->children.push_back(node1);

		Node* node2 = new Node();
		node2->data = "서버";
		programming->children.push_back(node2);

		Node* node3 = new Node();
		node3->data = "엔진";
		programming->children.push_back(node3);
	}

	// 기획 팀
	Node* planing = new Node();
	planing->data = "기획";
	root->children.push_back(planing);
	{
		Node* node1 = new Node();
		node1->data = "스토리";
		planing->children.push_back(node1);

		Node* node2 = new Node();
		node2->data = "레벨디자인";
		planing->children.push_back(node2);

		Node* node3 = new Node();
		node3->data = "컨텐츠";
		planing->children.push_back(node3);
	}

	// 프로그래밍 팀
	Node* art = new Node();
	art->data = "아트";
	root->children.push_back(art);
	{
		Node* node1 = new Node();
		node1->data = "원화";
		art->children.push_back(node1);

		Node* node2 = new Node();
		node2->data = "배경";
		art->children.push_back(node2);

		Node* node3 = new Node();
		node3->data = "모델";
		art->children.push_back(node3);
	}

	return root;
}

void PrintTree(Node* node, int depth = 0)
{
	// Tree의 전위순회 : 부모 - 왼쪽 자식들 - 오른쪽 자식들
	// Tree의 중위순회 : 왼쪽자식들 - 부모 - 오른쪽 자식들
	// Tree의 후위순회 : 왼쪽자식들 - 오른쪽자식들 - 부모

	for (int i = 0; i < depth; i++)
	{
		cout << "-";
	}

	// 전위순회
	 cout << node->data << endl;

	for (auto child : node->children)
	{
		PrintTree(child, depth + 1);
	}
	// 후위순회
	// cout << node->data << endl;
}

int main()
{
	Node* root = CreateTree();

	PrintTree(root);

	return 0;
}