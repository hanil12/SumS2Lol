#pragma once

class AlkaMap;
class AlkaItem;

class Brick
{
	friend class AlkaMap;
public:
	Brick(Vector size);
	~Brick();

	void Update();
	void Render(HDC hdc);

	void SetPos(Vector pos) { _pos = pos; }
	Vector GetPos() { return _pos; }

	shared_ptr<RectCollider> GetCollider() { return _body; }
	void SetItem(shared_ptr<AlkaItem> item);

	void Break_Brick();

private:
	bool _isActive = false;

	shared_ptr<RectCollider> _body;
	Vector _pos;

	weak_ptr<AlkaItem> _item;
};

