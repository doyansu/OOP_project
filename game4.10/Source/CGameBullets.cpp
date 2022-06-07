#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameBullets.h"
#include <cmath>

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//	�@��l�u
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
	// ���a��M
	CGamBullet_HandKnife::CGamBullet_HandKnife()
	{
		_damage = 4;
		_showPriority = 10;
		_bulletType = Type::HandKnife;
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
	//	�ĤH�����l�u
	CGamBullet_Enemy_No1::CGamBullet_Enemy_No1()
	{
		_damage = 1;
		_bulletType = Type::enemyNo1;
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

	/////////////////////////////////////////////////////////////////////////////
	//	�żu�j�l�u
	CGamBullet_Enemy_Slow::CGamBullet_Enemy_Slow()
	{
		_damage = 3;
		_bulletType = Type::slow;

		survive = 0;
	}

	void CGamBullet_Enemy_Slow::LoadBitmap()
	{
		_animaIter->AddBitmap(IDB_Bullet4, RGB(0, 0, 0));
	}

	void CGamBullet_Enemy_Slow::OnMove(CGameMap* map)
	{
		//	�ھ� _vector �i�沾��
		double speed = _moveSpeed * exp(-survive / (GAME_ONE_SECONED >> 2));	//	�ھڦs���ɶ��վ�Z��
		_mx += (int)((double)speed * _vector[0]);
		_my += (int)((double)speed * _vector[1]);

		survive++;
		if(survive > 3 * GAME_ONE_SECONED)	//	�s�b 3 ��
			this->SetEnable(false);

		//	��Ĳ��a�ϳ��𰱤�Ωж��q�D�s���B
		if (CGameBullet::CGameObj::Collision(map) || CGameBullet::CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL))
			this->SetEnable(false);
	}

	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// �a�_�S��
	CGamBullet_Effect_shock::CGamBullet_Effect_shock()
	{
		_damage = 3;
		_bulletType = Type::effect_shock;
	}

	void CGamBullet_Effect_shock::LoadBitmap()
	{
		_animaIter->SetDelayCount(2);
		_animaIter->AddBitmap(IDB_Bullet_effectShoch0_0, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_Bullet_effectShoch0_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_Bullet_effectShoch0_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_Bullet_effectShoch0_3, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_Bullet_effectShoch0_4, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_Bullet_effectShoch0_5, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_Bullet_effectShoch0_6, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_Bullet_effectShoch0_7, RGB(255, 255, 255));
	}

	void CGamBullet_Effect_shock::OnMove(CGameMap*)
	{
		this->SetEnable(false);
		this->SetDie(true);
	}

	/////////////////////////////////////////////////////////////////////////////
}