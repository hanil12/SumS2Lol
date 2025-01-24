#pragma once
class Line
{
public:
	struct HitResult
	{
		bool isCollision = false;
		Vector hitPoint = Vector();
	};

	Line(Vector start, Vector end);
	~Line();

	void Update();
	void Render(HDC hdc);

	HitResult IsCollision(shared_ptr<Line> other);

	Vector start;
	Vector end;

	void SetGreen() { _curPen = 0; }
	void SetRed() { _curPen = 1; }

private:
	UINT					_curPen = 0;
	vector<HPEN>			_pens;
};

