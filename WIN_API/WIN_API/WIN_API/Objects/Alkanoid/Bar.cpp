#include "framework.h"
#include "Bar.h"

#include "AlkaBall.h"

Bar::Bar()
{
	_pos = CENTER + Vector(0, 200);
	_body = make_shared<RectCollider>(_pos, Vector(140, 20));
}

Bar::~Bar()
{
}

void Bar::Init()
{
	for (int i = 0; i < 2; i++)
	{
		auto ball = make_shared<AlkaBall>(shared_from_this());
		ball->_isActive = false;
		ball->_isFired = false;

		_balls.push_back(ball);
	}

	_balls[0]->_isActive = true;
}

void Bar::Update()
{
	_body->Update();
	
	for (auto ball : _balls)
	{
		ball->Update();
	}
}

void Bar::Render(HDC hdc)
{
	_body->Render(hdc);
	for (auto ball : _balls)
	{
		ball->Render(hdc);
	}
}

void Bar::Input()
{
	_delayTime += 0.1f;

	if (GetKeyState('A') & 0x8000)
	{
		_pos += Vector(-1, 0) * 10;
	}

	if (GetKeyState('D') & 0x8000)
	{
		_pos += Vector(1, 0) * 10;
	}

	_body->SetCenter(_pos);

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		if (_delayTime > 3.0f)
		{
			_delayTime = 0.0f;

			auto ballIter = std::find_if(_balls.begin(), _balls.end(), [](shared_ptr<AlkaBall> a)-> bool 
				{
					if (a->IsFired())
						return false;
					return true;
				});

			if (ballIter != _balls.end())
				(*ballIter)->Fire(Vector(0, -1));
		}
	}
}

void Bar::TwoBall_Skill()
{
	auto iter = std::find_if(_balls.begin(), _balls.end(), [](shared_ptr<AlkaBall> ball)->bool 
		{
			if (ball->IsActive() == false)
				return true;
			return false;
		});

	if (iter != _balls.end())
		(*iter)->IsActive() = true;
}
