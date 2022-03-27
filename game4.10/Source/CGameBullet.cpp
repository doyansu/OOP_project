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
	}


	void CGameBullet::LoadBitmap()
	{
		CGameBullet::CGameObj::LoadBitmap(IDB_BALL); //test
	}

	void CGameBullet::OnMove(CGameMap* map)
	{
		_mx += _moveSpeed * _vector[0];
		_my += _moveSpeed * _vector[1];

		if (CGameBullet::CGameObj::Collision(map))
			CGameBullet::CGameObj::SetEnable(false);
	}

	/*void CGameBullet::OnShow(CGameMap* map)
	{

	}*/

}
