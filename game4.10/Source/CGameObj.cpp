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
		_animas.reserve(20);
		_animas.push_back(CAnimation());
		_tag = "null";
		_moveSpeed = 5;
		_needFree = true;
		Reset();
	}

	CGameObj::CGameObj(const CGameObj& other)
	{
		copy(other);
	}

	CGameObj& CGameObj::operator=(const CGameObj& other)
	{
		if (this != &other) 
			copy(other);
		return *this;
	}

	void CGameObj::copy(const CGameObj& other)	//	for copy construct、copy assigment
	{
		//this->_animas.assign(other._animas.begin(), other._animas.end());
		this->_animas = other._animas;
		this->_tag = other._tag;
		this->_moveSpeed = other._moveSpeed;
		this->_mx = other._mx;
		this->_my = other._my;
		this->_vector[0] = other._vector[0];
		this->_vector[1] = other._vector[1];
		this->_isMovingLeft = this->_isMovingRight = this->_isMovingUp = this->_isMovingDown = false;
		this->_isEnable = other._isEnable;
		this->_needFree = other._needFree;
		this->_animaIter = this->_animas.begin();
	}

	void CGameObj::Reset() 
	{
		_mx = _my = _vector[0] = _vector[1] = 0;
		_isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = false;
		_isEnable = true;
		_animaIter = _animas.begin();
	}

	bool CGameObj::Collision(CGameObj *other)	//	物件碰撞
	{
		return HitRectangle(other->GetX1(), other->GetY1(), other->GetX2(), other->GetY2());
	}

	bool CGameObj::Collision(CGameMap *map)	//	碰到地圖邊牆
	{
		int x1 = GetX1();
		int y1 = GetY1();
		int x2 = GetX2();
		int y2 = GetY2();

		return (!map->IsEmpty(x1, y1) || !map->IsEmpty(x1, y2) || !map->IsEmpty(x2, y1) || !map->IsEmpty(x2, y2));
	}

	bool CGameObj::HitRectangle(int tx1, int ty1, int tx2, int ty2)	//	矩形碰撞
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

	void CGameObj::OnShow(CGameMap* map)
	{
		_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));	
		_animaIter->OnShow();
	}

	void CGameObj::EnemyOnMove(CGameMap* map){
		const int range = 20;

		//_animaIter->OnMove();
		_mx += _vector[0];
		_my += _vector[1];

		if (CGameObj::Collision(map))
		{
			_mx -= _vector[0];
			_my -= _vector[1];
		}

		if ((rand() % range) == 0)
		{
			_vector[0] = -(_moveSpeed >> 1) + (rand() % _moveSpeed);
			_vector[1] = -(_moveSpeed >> 1) + (rand() % _moveSpeed);
		}

		
	}

	void CGameObj::OnMove(CGameMap* map)
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

	int CGameObj::GetVectorX()
	{
		return _vector[0];
	}

	int CGameObj::GetVectorY()
	{
		return _vector[1];
	}

	string CGameObj::GetTag()
	{
		return _tag;
	}

	bool CGameObj::NeedFree()	
	{
		return _needFree;
	}

	bool CGameObj::IsEnable()
	{
		return _isEnable;
	}

	void CGameObj::SetEnable(bool enable)
	{
		_isEnable = enable;
	}

	void CGameObj::SetFree(bool free)
	{
		_needFree = free;
	}

	void CGameObj::SetVector(int vx, int vy)
	{
		_vector[0] = vx;
		_vector[1] = vy;
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

	void CGameObj::SetTag(string tag)
	{
		_tag = tag;
	}

}