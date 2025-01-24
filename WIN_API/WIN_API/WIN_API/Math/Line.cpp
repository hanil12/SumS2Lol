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

Line::HitResult Line::IsCollision(shared_ptr<Line> other)
{
	Line::HitResult hitResult;

	Vector v1Dir = end - start;
	Vector a1 = other->start - start;
	Vector b1 = other->end - start;

	bool v1_Between = v1Dir.IsBetween(a1, b1);

	Vector v2Dir = other->end - other->start;
	Vector a2 = start - other->start;
	Vector b2 = end - other->start;

	bool v2_Between = v2Dir.IsBetween(a2, b2);

	hitResult.isCollision = v1_Between && v2_Between;
	if (hitResult.isCollision == false)
		return hitResult;

	// 충돌 했을 경우
	// 좌우 삼각형의 넓이 구하기
	float leftB = abs(v1Dir.Cross(a1));
	float rightB = abs(v1Dir.Cross(b1));

	float t = leftB / (leftB + rightB);
	hitResult.hitPoint = LERP(other->start, other->end, t);

	return hitResult;
}
