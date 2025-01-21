#include "pch.h"

#include "World.h"

// 과제
// 1. Creature 최상위 부모, 추상클래스
// 2. Goblin 10마리 vs (아처,메이지,나이트) 싸우기

int main()
{
	shared_ptr<World> world = make_shared<World>();

	while (true)
	{
		world->Update();

		if (world->End())
			break;
	}

	return 0;
}