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
		_atk, _cost = 0;
		_shootGap = 10;
		_bulletSpeed = 20;	
		_bullet.SetSpeed(_bulletSpeed);
		_fire = true;
		CGameWeapon::CGameObj::SetTag("weapon");
	}

	void CGameWeapon::LoadBitmap()
	{
		CGameWeapon::CGameObj::LoadBitmap(IDB_ERASER1);//test
		_bullet.LoadBitmap();

	}

	void CGameWeapon::OnMove(CGameMap* map)
	{
		for (int i = 0; i < (int)_bullets.size(); i++)
		{
			if (_bullets.at(i).IsEnable())
				_bullets.at(i).OnMove(map);
			else
				_bullets.erase(_bullets.begin() + i);
		}

		if (!_fire && --_fireCounter == 0)
			_fire = true;
		
	}

	void CGameWeapon::OnShow(CGameMap* map)
	{
		for (int i = 0; i < (int)_bullets.size(); i++)
		{
			_bullets.at(i).OnShow(map);
		}
		CGameWeapon::CGameObj::OnShow(map);
	}

	void CGameWeapon::Shoot(CGameMap* map, CGameObj* player)
	{
		if (_fire)
		{
			CGameBullet newBullet = _bullet;
			newBullet.SetXY(_mx, _my);
			newBullet.SetVector(player->GetVectorX(), player->GetVectorY());
			_bullets.push_back(newBullet);
			_fire = false;
			_fireCounter = _shootGap;
		}
	}

	bool CGameWeapon::isFire()
	{
		return _fire;
	}
}