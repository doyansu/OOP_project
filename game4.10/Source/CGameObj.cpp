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
		_mx = _my = 0;
		_moveSpeed = 5;
		_isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = false;
		CAnimation anima;
		_animas.push_back(anima);
		_animaIter = _animas.begin();
	}

	void CGameObj::Reset()
	{
		init();
	}

	int CGameObj::GetX1()
	{
		return _mx;
	}

	int CGameObj::GetY1()
	{
		return _my;
	}

	int CGameObj::GetX2()
	{
		return _mx + _animaIter->Width();
	}

	int CGameObj::GetY2()
	{
		return _my + _animaIter->Height();
	}

	bool CGameObj::Collision(CGameObj *other)
	{
		return HitRectangle(other->GetX1(), other->GetY1(), other->GetX2(), other->GetY2());
	}

	bool CGameObj::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = this->GetX1();				
		int y1 = this->GetY1();
		int x2 = this->GetX2();
		int y2 = this->GetY2();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	void CGameObj::LoadBitmap(int id)
	{
		_animaIter->AddBitmap(id, RGB(255, 255, 255));			
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
		_mx = x;
		_my = y;
	}

	void CGameObj::SetSpeed(int speed)
	{
		_moveSpeed = speed;
	}

	void CGameObj::OnShow(CGameMap* map)
	{
		_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));
		_animaIter->OnShow();
	}

	void CGameObj::OnMove()
	{
		_animaIter->OnMove();
		if (_isMovingLeft)
			_mx -= _moveSpeed;
		if (_isMovingRight)
			_mx += _moveSpeed;
		if (_isMovingUp)
			_my -= _moveSpeed;
		if (_isMovingDown)
			_my += _moveSpeed;
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