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
		Reset();
	}


	void CGameBullet::LoadBitmap()
	{
		CGameBullet::CGameObj::LoadBitmap(IDB_BALL); //test
	}

	void CGameBullet::OnMove(CGameMap* map)
	{

	}

	/*void CGameBullet::OnShow(CGameMap* map)
	{

	}*/

}
