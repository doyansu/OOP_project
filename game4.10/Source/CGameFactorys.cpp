#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameFactorys.h"
#include "CGameWeapons.h"
#include "CGameEnemys.h"

namespace game_framework
{
	void Registrar::Registrars()	//	註冊所有工廠可生產物件
	{
		/////////////////////////////////////////////////////////////////////////////
		// 武器
		static ProductRegistrar<CGameWeapon, CGameWeapon_Init> w1((int)CGameWeapon::Type::INIT);
		static ProductRegistrar<CGameWeapon, CGameWeapon_NewInit> w2((int)CGameWeapon::Type::NEWINIT);
		static ProductRegistrar<CGameWeapon, CGameWeapon_AK47> w3((int)CGameWeapon::Type::AK47);
		static ProductRegistrar<CGameWeapon, CGameWeapon_Enemy_0> w4((int)CGameWeapon::Type::enemy_0);
		static ProductRegistrar<CGameWeapon, CGameWeapon_Enemy_slow> w5((int)CGameWeapon::Type::enemy_slow);
		/////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////
		// 子彈
		static ProductRegistrar<CGameBullet, CGamBullet_Init> b1((int)CGameBullet::Type::INIT);
		static ProductRegistrar<CGameBullet, CGamBullet_HandKnife> b2((int)CGameBullet::Type::HandKnife);
		static ProductRegistrar<CGameBullet, CGamBullet_Enemy_No1> b3((int)CGameBullet::Type::enemyNo1);
		static ProductRegistrar<CGameBullet, CGamBullet_Enemy_Slow> b4((int)CGameBullet::Type::slow);
		static ProductRegistrar<CGameBullet, CGamBullet_Effect_shock> b5((int)CGameBullet::Type::effect_shock);
		
		/////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////
		// 敵人
		static ProductRegistrar<CEnemy, CGameEnemy_Init> e1((int)CEnemy::Type::INIT);
		static ProductRegistrar<CEnemy, CGameEnemy_SNOW_0> e2((int)CEnemy::Type::SNOW_SLOW);
		static ProductRegistrar<CEnemy, CGameEnemy_SNOW_Monkey> e3((int)CEnemy::Type::SNOW_Monkey_0);
		static ProductRegistrar<CEnemy, CGameEnemy_Crystal> e4((int)CEnemy::Type::crystal);
		static ProductRegistrar<CEnemy, CGameEnemy_Gold> e5((int)CEnemy::Type::gold);
		static ProductRegistrar<CEnemy, CGameEnemy_Gold> e6((int)CEnemy::Type::BOSS_SNOW_0);
		
		/////////////////////////////////////////////////////////////////////////////
			
			
	}

}