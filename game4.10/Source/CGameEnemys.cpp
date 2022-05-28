#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameEnemys.h"

namespace game_framework {

	CGameEnemy_Init::CGameEnemy_Init()
	{

	}

	void CGameEnemy_Init::LoadBitmap()
	{
		_animaIter = GetAnima(CEnemy::Anima::RUN_R);
		_animaIter->AddBitmap(IDB_enemy0_0, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_3, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_4, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::RUN_L);
		_animaIter->AddBitmap(IDB_ENEMY0_0_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY0_1_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY0_2_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY0_3_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY0_4_L, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::DIE);
		_animaIter->AddBitmap(IDB_enemy0_die, RGB(255, 255, 255));

		*GetAnima(Anima::APPEARANCE) = CAnimationEnemyAppear::Instance();


		_animaIter = _animas.begin();


		// ªZ¾¹³]©w
		_weapon = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::Type::INIT);
		_weapon->SetUser(this);
		_weapon->SetAttributes(1, 0, 5, 50);
		_weapon->SetTarget("player");
	}
}