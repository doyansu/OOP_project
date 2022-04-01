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
		const int AnimaSize = 2;
		_animas.clear();
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation());
		_atk, _cost = 0;
		_shootDelay = 10;
		_bulletSpeed = 20;
		_DT = 1;
		_bullet.SetSpeed(_bulletSpeed);
		_fire = true;
		_user = nullptr;
		CGameWeapon::CGameObj::SetTag("weapon");
	}

	void CGameWeapon::SetUser(CGameObj* user)
	{
		_user = user;
		if (_user->GetTag() == "player")
			_bullet.SetTarget("enemy");
		else
			_bullet.SetTarget("player");
	}

	void CGameWeapon::SetAttributes(int atk, int cost, int bulletSpeed, int shootDelay)
	{
		_atk = atk;
		_cost = cost;
		_bulletSpeed = bulletSpeed;
		_shootDelay = shootDelay;
		_bullet.SetSpeed(_bulletSpeed);
		_bullet.SetDamage(_atk);
	}

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
		if (_user == nullptr)
			return;
		// 動畫判斷
		if (_DT == 1) {
			CGameWeapon::CGameObj::_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Right);
			this->SetXY(_user->CenterX(), _user->CenterY());
		}
		else if (_DT == 0) {
			CGameWeapon::CGameObj::_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Left);
			this->SetXY(_user->CenterX() - (this->GetX2() - this->GetX1()), _user->CenterY());
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
			if (_user)
				_bullet.SetXY(_user->CenterX(), _user->CenterY());
			else 
				_bullet.SetXY(_mx, _my);
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
}