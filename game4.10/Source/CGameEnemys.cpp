#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameEnemys.h"
#include "CAnimationEnemyAppear.h"
#include "CGameFactorys.h"
#include "CCharacter.h"

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	//	狙擊兵
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
	//	霰彈兵
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

	/////////////////////////////////////////////////////////////////////////////
	//	小雪猿
	CGameEnemy_SNOW_Monkey::CGameEnemy_SNOW_Monkey()
	{
		_hp = _maxHp = 15;
		state = STATE::RANDMOVE;
	}


	void CGameEnemy_SNOW_Monkey::LoadBitmap()
	{
		_animaIter = GetAnima(CEnemy::Anima::RUN_R);
		_animaIter->AddBitmap(IDB_enemy2_0, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy2_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy2_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy2_3, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy2_4, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::RUN_L);
		_animaIter->AddBitmap(IDB_ENEMY2_0_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY2_1_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY2_2_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY2_3_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY2_4_L, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::DIE);
		_animaIter->AddBitmap(IDB_enemy2_die, RGB(255, 255, 255));

		*GetAnima(Anima::APPEARANCE) = CAnimationEnemyAppear::Instance();


		_animaIter = _animas.begin();


		// 武器設定
		/*_weapon = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::Type::enemy_slow);
		_weapon->SetUser(this);
		_weapon->SetTarget("player");*/
	}

	/*
	void CGameEnemy_SNOW_Monkey::OnMove(CGameMap* map)
	{
		if (!GetAnima(Anima::APPEARANCE)->IsFinalBitmap())
		{
			GetAnima(Anima::APPEARANCE)->OnMove();
			return;
		}

		_animaIter->OnMove();

		CGameObj* player = CCharacter::Instance();
		const double MAXSEARCH = 300.0;	// 最大搜索範圍
		double d = MAXSEARCH;
		double vx = 0;
		double vy = 0;

		// 找到玩家
		if (player && !player->hasObstacle(map, this) && d < MAXSEARCH)
		{
			d = this->Distance(player);
			vx = (double)(player->CenterX() - this->CenterX()) / d;
			vy = (double)(player->CenterY() - this->CenterY()) / d;
			// 切換動畫
			if (vx > 0)
				_animaIter = GetAnima(CEnemy::Anima::RUN_R);
			else
				_animaIter = GetAnima(CEnemy::Anima::RUN_L);
		}

		// 敵人移動
		switch (state)
		{
		case game_framework::CGameEnemy_SNOW_Monkey::STATE::RANDMOVE:
		{
			const int randomRange = 20;	// 隨機變方向

			if ((rand() % randomRange) == 0)
			{
				_vector[0] = (double)(-100 + rand() % 201) / 100.0;
				_vector[1] = (double)(-100 + rand() % 201) / 100.0;
			}

			// 找到玩家
			if (player && !player->hasObstacle(map, this) && rand() % 10 == 0)
			{
				_tx = player->GetX1();
				_ty = player->GetY1();
				state = STATE::MOVETO;
			}
			break;
		}
		case game_framework::CGameEnemy_SNOW_Monkey::STATE::MOVETO:
		{
			double td = sqrt((_tx - _mx) * (_tx - _mx) + (_ty - _my) * (_ty - _my));
			_vector[0] = (_tx - _mx) / td;
			_vector[1] = (_ty - _my) / td;
			if (_tx >= this->GetX1() && _ty >= this->GetY1() && _tx <= this->GetX2() && _ty <= this->GetY2())
			{
				CGameBullet* shock = ProductFactory<CGameBullet>::Instance().GetProduct((int)CGameBullet::Type::effect_shock);
				shock->AddTarget("player");
				shock->SetXY(this->CenterX() - (shock->GetWidth() >> 1), this->CenterY() - (shock->GetHeight() >> 1));
				CGameObj::AddObj(shock);
				state = STATE::RANDMOVE;
				break;
			}
		}
		default:
			break;
		}
		

		int Speed = _moveSpeed;
		int dx = (int)((double)Speed * _vector[0]), dy = (int)((double)Speed * _vector[1]);
		
		_mx += dx;
		_my += dy;

		if (CGameObj::Collision(map) || CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL))
		{
			_mx -= dx;
			_my -= dy;
			
			for (int i = 0; i < Speed; i++)
			{
				dx -= 
			}
		}

		_mx += dx;
		_my += dy;
		
	}*/

	/////////////////////////////////////////////////////////////////////////////
	
}