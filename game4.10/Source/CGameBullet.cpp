#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameBullet.h"

namespace game_framework
{
	CGameBullet::CGameBullet()
	{
		init();
	}

	void CGameBullet::init()
	{
		_damage = 4;
		_target = "";
		_showPriority = 5;
		CGameBullet::CGameObj::SetTag("bullet");
	}


	void CGameBullet::LoadBitmap()
	{
		CGameBullet::CGameObj::_animaIter->AddBitmap(IDB_Bullet0, RGB(255, 255, 255)); //test image
	}

	void CGameBullet::OnMove(CGameMap* map)
	{
		//	根據 _vector 進行移動
		_mx += (int)((double)_moveSpeed * _vector[0]);
		_my += (int)((double)_moveSpeed * _vector[1]);

		//	接觸到地圖圍牆停止或房間通道連接處
		if (CGameBullet::CGameObj::Collision(map) || CGameBullet::CGameObj::Collision(map, CGameMap::MapContent::AISLEWALL))
			CGameBullet::CGameObj::SetEnable(false);
	}

	/*void CGameBullet::OnShow(CGameMap* map)
	{

	}*/

	void CGameBullet::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		if (other->GetTag() == _target)
		{
			this->SetEnable(false);
			other->TakeDmg(_damage);
		}
	}

	void CGameBullet::SetTarget(string target)
	{
		_target = target;
	}

	void CGameBullet::SetDamage(int damage)
	{
		_damage = damage;
	}

}
