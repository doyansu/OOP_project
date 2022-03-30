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
		_damage = 0;
		CGameBullet::CGameObj::SetTag("bullet");
	}


	void CGameBullet::LoadBitmap()
	{
		CGameBullet::CGameObj::_animaIter->AddBitmap(IDB_BALL, RGB(0, 0, 0)); //test image
	}

	void CGameBullet::OnMove(CGameMap* map)
	{
		//	根據 _vector 進行移動
		_mx += (int)((double)_moveSpeed * _vector[0]);
		_my += (int)((double)_moveSpeed * _vector[1]);

		//	接觸到地圖圍牆停止
		if (CGameBullet::CGameObj::Collision(map))
			CGameBullet::CGameObj::SetEnable(false);
	}

	/*void CGameBullet::OnShow(CGameMap* map)
	{

	}*/

	void CGameBullet::OnObjCollision(CGameObj* other)
	{
		if (other->GetTag() == "enemy")
			this->SetEnable(false);
	}

}
