#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameObj.h"

namespace game_framework {

	CGameObj::CGameObj()
	{
		init();
	}

	void CGameObj::init()
	{
		_x = _y = 0;
		_moveSpeed = 5;
		_isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = false;
	}

	void CGameObj::Reset()
	{
		init();
	}

	int CGameObj::GetX1()
	{
		return _x;
	}

	int CGameObj::GetY1()
	{
		return _y;
	}

	int CGameObj::GetX2()
	{
		return _x + _initbmp.Width();
	}

	int CGameObj::GetY2()
	{
		return _y + _initbmp.Height();
	}

	bool CGameObj::Collision(CGameObj *other)
	{
		return HitRectangle(other->GetX1(), other->GetY1(), other->GetX2(), other->GetY2());
	}

	bool CGameObj::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = _x;				
		int y1 = _y;				
		int x2 = x1 + _initbmp.Width();
		int y2 = y1 + _initbmp.Height();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	void CGameObj::LoadBitmap(int id)
	{
		_initbmp.LoadBitmap(id, RGB(255, 255, 255));			
	}

	void CGameObj::SetMovingDown(bool flag)
	{
		_isMovingDown = flag;
	}

	void CGameObj::SetMovingLeft(bool flag)
	{
		_isMovingLeft = flag;
	}

	void CGameObj::SetMovingRight(bool flag)
	{
		_isMovingRight = flag;
	}

	void CGameObj::SetMovingUp(bool flag)
	{
		_isMovingUp = flag;
	}

	void CGameObj::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void CGameObj::SetSpeed(int speed)
	{
		_moveSpeed = speed;
	}

	void CGameObj::OnShow(CGameMap* map)
	{
		_initbmp.SetTopLeft(map->ScreenX(_x), map->ScreenY(_y));
		_initbmp.ShowBitmap();
	}

	void CGameObj::OnMove()
	{
		if (_isMovingLeft)
			_x -= _moveSpeed;
		if (_isMovingRight)
			_x += _moveSpeed;
		if (_isMovingUp)
			_y -= _moveSpeed;
		if (_isMovingDown)
			_y += _moveSpeed;
	}

	void CGameObj::OnKeyUp(char nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_LEFT)
			this->SetMovingLeft(false);
		if (nChar == KEY_RIGHT)
			this->SetMovingRight(false);
		if (nChar == KEY_UP)
			this->SetMovingUp(false);
		if (nChar == KEY_DOWN)
			this->SetMovingDown(false);
	}

	void CGameObj::OnKeyDown(char nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_LEFT)
			this->SetMovingLeft(true);
		if (nChar == KEY_RIGHT)
			this->SetMovingRight(true);
		if (nChar == KEY_UP)
			this->SetMovingUp(true);
		if (nChar == KEY_DOWN)
			this->SetMovingDown(true);
	}

}