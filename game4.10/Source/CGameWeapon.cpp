#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameWeapon.h"
#include "CGameObjCenter.h"


namespace game_framework
{
	CGameWeapon::CGameWeapon()
	{
		// 動畫載入
		const int AnimaSize = 2;
		_animas.clear();
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation());
		// 屬性設定
		_fire = true;
		_cost = 0;
		_shootDelay = 10;
		_bulletSpeed = 20;
		_DT = 1;
		CGameWeapon::CGameObj::SetTag("weapon");
		// 子彈設定
		_bullet.SetSpeed(_bulletSpeed);
	}

	/*CGameWeapon::CGameWeapon(const CGameWeapon& other)
	{
		copy(other);
	}

	CGameWeapon& CGameWeapon::operator=(const CGameWeapon& other)
	{
		if (this != &other)
			copy(other);
		return *this;
	}*/

	/*void CGameWeapon::copy(const CGameWeapon& other)
	{
		this->_fire = other._fire;
		this->_cost = other._cost;
		this->_bulletSpeed = other._bulletSpeed;
		this->_shootDelay = other._shootDelay;
		this->_fireCounter = other._fireCounter;
		this->_DT = other._DT;
		this->_bullet = other._bullet;
	}*/

	void CGameWeapon::LoadBitmap()
	{
		CGameWeapon::CGameObj::_animaIter = GetAnima(CGameWeapon::Anima::Right);
		CGameWeapon::CGameObj::_animaIter->AddBitmap(IDB_weapon1, RGB(255, 255, 255));
				
		CGameWeapon::CGameObj::_animaIter = GetAnima(CGameWeapon::Anima::Left);
		CGameWeapon::CGameObj::_animaIter->AddBitmap(IDB_weapon1_l, RGB(255, 255, 255));

		CGameWeapon::CGameObj::_animaIter = _animas.begin();

		_bullet.LoadBitmap();
	}

	void CGameWeapon::OnMove(CGameMap* map)
	{
		CGameWeapon::CGameObj::_animaIter->OnMove();

		// 動畫判斷
		if (_DT == 1) {
			CGameWeapon::CGameObj::_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Right);
		}
		else if (_DT == 0) {
			CGameWeapon::CGameObj::_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Left);
		}

		//	射擊間隔計數
		if (!_fire && --_fireCounter == 0)
			_fire = true;
		
	}

	void CGameWeapon::OnShow(CGameMap* map)
	{
		CGameWeapon::CGameObj::OnShow(map);
	}

	void CGameWeapon::Shoot(double x, double y)
	{
		if (_fire)
		{
			if(_DT == 0)
				_bullet.SetXY(this->GetX1(), this->CenterY());
			else if (_DT == 1)
				_bullet.SetXY(this->GetX2(), this->CenterY());

			_bullet.SetVector(x, y);
			CGameObjCenter::AddObj(new CGameBullet(_bullet));
			_fire = false;
			_fireCounter = _shootDelay;
		}
	}

	bool CGameWeapon::CanFire() 
	{
		return _fire;
	}

	vector<CAnimation>::iterator CGameWeapon::GetAnima(Anima type)
	{
		vector<CAnimation>::iterator anima = _animas.begin();
		switch (type)
		{
		case game_framework::CGameWeapon::Anima::Right:
			anima = _animas.begin();
			break;
		case game_framework::CGameWeapon::Anima::Left:
			anima = _animas.begin() + 1;
			break;
		default:
			break;
		}
		return anima;
	}

	void CGameWeapon::SetDT(int DT)
	{
		_DT = DT;
	}

	void CGameWeapon::SetTarget(string target)
	{
		_bullet.SetTarget(target);
	}

	void CGameWeapon::SetAttributes(int atk, int cost, int bulletSpeed, int shootDelay)
	{
		_cost = cost;
		_bulletSpeed = bulletSpeed;
		_shootDelay = shootDelay;
		_bullet.SetSpeed(_bulletSpeed);
		_bullet.SetDamage(atk);
	}
}