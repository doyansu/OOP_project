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
		//	�ھ� _vector �i�沾��
		_mx += (int)((double)_moveSpeed * _vector[0]);
		_my += (int)((double)_moveSpeed * _vector[1]);

		//	��Ĳ��a�ϳ��𰱤�
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
