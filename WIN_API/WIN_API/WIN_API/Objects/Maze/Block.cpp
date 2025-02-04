#include "framework.h"
#include "Block.h"

Block::Block()
: RectCollider(Vector(0,0), Vector(13,13))
{
	_brushes.push_back(CreateSolidBrush(BLACK)); // NONE
	_brushes.push_back(CreateSolidBrush(GREEN)); // ABLE
	_brushes.push_back(CreateSolidBrush(RED)); // BLOCKED
	_brushes.push_back(CreateSolidBrush(RGB(101, 3, 62))); // Player

	_pens.push_back(CreatePen(1, 3, RGB(101, 3, 62)));
}

Block::~Block()
{
	for (auto brush : _brushes)
	{
		DeleteObject(brush);
	}
}

void Block::Update()
{
	RectCollider::Update();
}

void Block::Render(HDC hdc)
{
	SelectObject(hdc,_brushes[static_cast<int>(_curType)]);
	_curPen = static_cast<int>(_curType);
	RectCollider::Render(hdc);
}
