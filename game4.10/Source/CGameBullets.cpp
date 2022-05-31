#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameBullets.h"

namespace game_framework
{

	CGamBullet_Init::CGamBullet_Init()
	{

	}

	CGamBullet_Init& CGamBullet_Init::Instance()
	{
		static CGamBullet_Init Instance;
		static bool isLoad = false;
		if (isLoad == false)
		{
			Instance.LoadBitmap();
			isLoad = true;
		}
		return Instance;
	}

	void CGamBullet_Init::LoadBitmap()
	{
		_animaIter->AddBitmap(IDB_Bullet0, RGB(255, 255, 255)); //test image
	}
}