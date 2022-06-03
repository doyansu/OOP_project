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
		_animaIter->SetDelayCount(1);
		_animaIter->AddBitmap(IDB_handknife_right, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right1, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right2, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right3, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right4, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right5, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right6, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right7, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right8, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right9, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right10, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right11, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right12, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_handknife_right13, RGB(0, 0, 0));
	}

	void CGamBullet_HandKnife::OnMove(CGameMap*)
	{
		this->SetEnable(false);
		this->SetDie(true);
	}

	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	敵人一般子彈
	CGamBullet_Enemy_No1::CGamBullet_Enemy_No1()
	{
		_damage = 1;
		_bulletType = Type::enemyNo1;
		this->AddTarget("player");
	}

	CGamBullet_Enemy_No1& CGamBullet_Enemy_No1::Instance()
	{
		static CGamBullet_Enemy_No1 Instance;
		static bool isLoad = false;
		if (isLoad == false)
		{
			Instance.LoadBitmap();
			isLoad = true;
		}
		return Instance;
	}

	void CGamBullet_Enemy_No1::LoadBitmap()
	{
		_animaIter->AddBitmap(IDB_Bullet_e, RGB(255, 255, 255));
	}
	/////////////////////////////////////////////////////////////////////////////
}