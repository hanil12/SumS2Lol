#include "framework.h"
#include "Line.h"

Line::Line(Vector start, Vector end)
: start(start), end(end)
{
	_pens.push_back(CreatePen(1, 3, GREEN));
	_pens.push_back(CreatePen(1, 3, RED));
}

Line::~Line()
{
	for (auto pen : _pens)
	{
		DeleteObject(pen);
	}
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curPen]);

	MoveToEx(hdc, start.x, start.y, nullptr);
	LineTo(hdc, end.x, end.y);
}

bool Line::IsCollision(shared_ptr<Line> other)
{
	Vector v1Dir = end - start;
	Vector a1 = other->start - start;
	Vector b1 = other->end - start;

	bool v1_Between = v1Dir.IsBetween(a1, b1);

	Vector v2Dir = other->end - other->start;
	Vector a2 = start - other->start;
	Vector b2 = end - other->start;

	bool v2_Between = v2Dir.IsBetween(a2, b2);

	return v1_Between && v2_Between;
}
