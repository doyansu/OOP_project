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
	void Registrar::Registrars()	//	���U�Ҧ��u�t�i�Ͳ�����
	{
		/////////////////////////////////////////////////////////////////////////////
		// �Z��
		static ProductRegistrar<CGameWeapon, CGameWeapon_Init> w1((int)CGameWeapon::Type::INIT);
		static ProductRegistrar<CGameWeapon, CGameWeapon_NewInit> w2((int)CGameWeapon::Type::NEWINIT);
		static ProductRegistrar<CGameWeapon, CGameWeapon_AK47> w3((int)CGameWeapon::Type::AK47);
		static ProductRegistrar<CGameWeapon, CGameWeapon_Enemy_0> w4((int)CGameWeapon::Type::enemy_0);
		static ProductRegistrar<CGameWeapon, CGameWeapon_Enemy_slow> w5((int)CGameWeapon::Type::enemy_slow);
		/////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////
		// �l�u
		static ProductRegistrar<CGameBullet, CGamBullet_Init> b1((int)CGameBullet::Type::INIT);
		static ProductRegistrar<CGameBullet, CGamBullet_HandKnife> b2((int)CGameBullet::Type::HandKnife);
		static ProductRegistrar<CGameBullet, CGamBullet_Enemy_No1> b3((int)CGameBullet::Type::enemyNo1);
		static ProductRegistrar<CGameBullet, CGamBullet_Enemy_Slow> b4((int)CGameBullet::Type::slow);
		/////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////
		// �ĤH
		static ProductRegistrar<CEnemy, CGameEnemy_Init> e1((int)CEnemy::Type::INIT);
		static ProductRegistrar<CEnemy, CGameEnemy_SNOW_0> e2((int)CEnemy::Type::SNOW_SLOW);
		/////////////////////////////////////////////////////////////////////////////
			
			
	}

}