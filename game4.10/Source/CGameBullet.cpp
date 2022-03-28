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
		CGameBullet::CGameObj::LoadBitmap(IDB_BALL); //test image
	}

	void CGameBullet::OnMove(CGameMap* map)
	{
		//	�ھ� _vector �i�沾��
		_mx += _moveSpeed * _vector[0];
		_my += _moveSpeed * _vector[1];

		//	��Ĳ��a�ϳ��𰱤�
		if (CGameBullet::CGameObj::Collision(map))
			CGameBullet::CGameObj::SetEnable(false);
	}

	/*void CGameBullet::OnShow(CGameMap* map)
	{

	}*/

}
