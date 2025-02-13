#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
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

//           이진탐색트리    vs     해쉬테이블 (표)
//            Node(key,data)       pair(key, data) 
//           key로 정렬             해쉬(key...Algorithm) => Index
// 탐색시간    logN                  1
// 삽입시간    logN                  1
// 삭제        logN                  1

// => 이진탐색트리를 쓰는 이유
// 1. 데이터를 많이 쓴다. (데이터 파편화가 되어있으면 해시테이블을 쓰기 힘들 수 있다.)
// 2. 해쉬함수의 성능이 떨어질 경우 '체이닝' 발생

class Player
{
public:
	bool operator<(const Player& other) const
	{
		return hp < other.hp;
	}

	bool operator==(const Player& other) const
	{
		return hp == other.hp;
	}

	int hp;
	int atk;
};

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

	map<string, int> m;

	if(m.count("Hanil1") == 0)
		m["Hanil1"] = 1;	
	auto iter = m.insert(make_pair<string, int>("Hanil2", 2));

	for (auto p : m)
	{
		cout << p.first << "... " << p.second << endl;
	}

	map<Player, int> pm;
	pm[{10, 5}] = 5;

	return 0;
}
