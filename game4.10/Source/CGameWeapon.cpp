#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameWeapon.h"



namespace game_framework
{
	CGameWeapon::CGameWeapon()
	{
		init();
	}

	void CGameWeapon::init()
	{
		const int AnimaSize = 2;
		CAnimation addAnima;
		_animas.clear();
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(addAnima);
		_atk, _cost = 0;
		_shootGap = 10;
		_bulletSpeed = 20;	
		_bullet.SetSpeed(_bulletSpeed);
		_bullet.SetFree(true);
		_fire = true;
		CGameWeapon::CGameObj::SetTag("weapon");
	}

	void CGameWeapon::LoadBitmap()
	{
		CGameWeapon::CGameObj::_animaIter = GetAnima(Anima::Right);
		CGameWeapon::CGameObj::_animaIter->AddBitmap(IDB_weapon1, RGB(255, 255, 255));
				
		CGameWeapon::CGameObj::_animaIter = GetAnima(Anima::Left);
		CGameWeapon::CGameObj::_animaIter->AddBitmap(IDB_weapon1_l, RGB(255, 255, 255));

		CGameWeapon::CGameObj::_animaIter = _animas.begin();

		_bullet.LoadBitmap();
	}

	void CGameWeapon::OnMove(CGameMap* map)
	{

		//	®gÀ»¶¡¹j­p¼Æ
		if (!_fire && --_fireCounter == 0)
			_fire = true;
		
	}

	void CGameWeapon::OnShow(CGameMap* map)
	{
		CGameWeapon::CGameObj::OnShow(map);
	}

	void CGameWeapon::Shoot(CGameMap* map, CGameObj* player)
	{
		if (_fire)
		{
			_bullet.SetXY(_mx, _my);
			_bullet.SetVector(player->GetVectorX(), player->GetVectorY());
			CGameObjCenter::AddObj(new CGameBullet(_bullet));
			_fire = false;
			_fireCounter = _shootGap;
		}
	}

	bool CGameWeapon::CanFire()
	{
		return _fire;
	}

	void CGameWeapon::DT_D(int dt)
	{
		if (dt == 1) {
			CGameWeapon::CGameObj::_animaIter = CGameWeapon::GetAnima(Anima::Right);
		}
		else if (dt == 0) {
			CGameWeapon::CGameObj::_animaIter = CGameWeapon::GetAnima(Anima::Left);
			this -> _mx -= 30;
		}
		CGameWeapon::CGameObj::_animaIter->OnMove();
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
}