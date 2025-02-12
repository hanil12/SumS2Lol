#include "framework.h"
#include "Program.h"

#include "Scene/PaintScene.h"
#include "Scene/CollisionScene.h"
#include "Scene/LineScene.h"
#include "Scene/LineCollisionScene.h"
#include "Scene/CannonScene.h"
#include "Scene/MazeScene.h"
#include "Scene/AlkanoidScene.h"
#include <time.h>

HDC Program::backbuffer = nullptr;
Program::Program()
{
	srand(time(nullptr));

	_scene = make_shared<AlkanoidScene>();

	HDC hdc = GetDC(hWnd);

	backbuffer = CreateCompatibleDC(hdc);
	_hBitMap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT); // 그림을 그릴 도화지
	SelectObject(backbuffer, _hBitMap);
}

Program::~Program()
{
	DeleteObject(backbuffer);
	DeleteObject(_hBitMap);
}

void Program::Update()
{
	_scene->Update();
}

void Program::Render(HDC hdc)
{
	PatBlt(backbuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, BLACKNESS);

	_scene->Render(backbuffer);

	// 복사
	BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		backbuffer, 0, 0, SRCCOPY);
}
