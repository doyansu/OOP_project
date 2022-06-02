#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameBullets.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//	一般子彈
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
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// 玩家手刀
	CGamBullet_HandKnife::CGamBullet_HandKnife()
	{
		_damage = 4;
		_showPriority = 10;
		_bulletType = Type::HandKnife;
		this->AddTarget("enemy");
	}

	CGamBullet_HandKnife& CGamBullet_HandKnife::Instance()
	{
		static CGamBullet_HandKnife Instance;
		static bool isLoad = false;
		if (isLoad == false)
		{
			Instance.LoadBitmap();
			isLoad = true;
		}
		return Instance;
	}

	void CGamBullet_HandKnife::LoadBitmap()
	{
		_animaIter->SetDelayCount(10);
		_animaIter->AddBitmap(IDB_handknife_right, RGB(0, 0, 0)); //test image
	}

	void CGamBullet_HandKnife::OnMove(CGameMap*)
	{
		this->SetEnable(false);
		this->SetDie(true);
	}

	void CGamBullet_HandKnife::OnDie(CGameMap*)
	{
		//	動畫播完再釋放
		if (!_animaIter->IsFinalBitmap())
		{
			_animaIter->OnMove();
		}
		else
		{
			this->SetDie(false);
		}
	}
	/////////////////////////////////////////////////////////////////////////////
}