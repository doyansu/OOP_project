#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameEnemys.h"
#include "CAnimationEnemyAppear.h"
#include "CGameFactorys.h"

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	CGameEnemy_Init::CGameEnemy_Init()
	{
		_hp = _maxHp = 10;
	}

	CGameEnemy_Init& CGameEnemy_Init::Instance()
	{
		static CGameEnemy_Init Instance;
		static bool isLoad = false;
		if (isLoad == false)
		{
			Instance.LoadBitmap();
			isLoad = true;
		}
		return Instance;
	}

	void CGameEnemy_Init::LoadBitmap()
	{
		_animaIter = GetAnima(CEnemy::Anima::RUN_R);
		_animaIter->AddBitmap(IDB_enemy1_0, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy1_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy1_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy1_3, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy1_4, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::RUN_L);
		_animaIter->AddBitmap(IDB_ENEMY1_0_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY1_1_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY1_2_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY1_3_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY1_4_L, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::DIE);
		_animaIter->AddBitmap(IDB_enemy1_die, RGB(255, 255, 255));

		*GetAnima(Anima::APPEARANCE) = CAnimationEnemyAppear::Instance();


		_animaIter = _animas.begin();


		// 武器設定
		_weapon = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::Type::enemy_0);
		_weapon->SetUser(this);
		_weapon->SetTarget("player");
	}
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////

	CGameEnemy_SNOW_0::CGameEnemy_SNOW_0()
	{
		_hp = _maxHp = 10;
	}

	
	void CGameEnemy_SNOW_0::LoadBitmap()
	{
		_animaIter = GetAnima(CEnemy::Anima::RUN_R);
		_animaIter->AddBitmap(IDB_enemy1_0, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy1_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy1_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy1_3, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy1_4, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::RUN_L);
		_animaIter->AddBitmap(IDB_ENEMY1_0_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY1_1_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY1_2_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY1_3_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY1_4_L, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::DIE);
		_animaIter->AddBitmap(IDB_enemy1_die, RGB(255, 255, 255));

		*GetAnima(Anima::APPEARANCE) = CAnimationEnemyAppear::Instance();


		_animaIter = _animas.begin();


		// 武器設定
		_weapon = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::Type::enemy_slow);
		_weapon->SetUser(this);
		_weapon->SetTarget("player");
	}

	/////////////////////////////////////////////////////////////////////////////
}