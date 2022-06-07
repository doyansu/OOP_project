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
#include "CGameTrackObj.h"

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	//	狙擊兵
	CGameEnemy_Init::CGameEnemy_Init()
	{
		_hp = _maxHp = 15;
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
		_hp = _maxHp = 15;
		_maxSearch = 250;
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
		_hp = _maxHp = 9;
		_maxSearch = 250;
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
		int Speed = _moveSpeed;

		// 找到玩家
		if (player && !player->hasObstacle(map, this))
		{
			d = this->Distance(player);
			vx = (double)(player->CenterX() - this->CenterX()) / d;
			vy = (double)(player->CenterY() - this->CenterY()) / d;
			// 切換動畫
			if (d < MAXSEARCH)
			{
				if (vx > 0)
					_animaIter = GetAnima(CEnemy::Anima::RUN_R);
				else
					_animaIter = GetAnima(CEnemy::Anima::RUN_L);
			}
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
			if (rand() % 100 == 0 && player && !player->hasObstacle(map, this))
			{
				_tx = player->CenterX();
				_ty = player->CenterY();

				_vector[0] = vx;
				_vector[1] = vy;

				_maxTrackTime = 3 * GAME_ONE_SECONED + rand() % (2 * GAME_ONE_SECONED);
				state = STATE::MOVETO;
			}
			break;
		}
		case game_framework::CGameEnemy_SNOW_Monkey::STATE::MOVETO:
		{
			Speed <<= 1;
			_maxTrackTime--;
			double td = sqrt((this->CenterX() - _tx) * (this->CenterX() - _tx) + (this->CenterY() - _ty) * (this->CenterY() - _ty));
			if (_maxTrackTime == 0 || td < 45)
			{
				_maxTrackTime = 0;
				_vector[0] = 0;
				_vector[1] = 0;
				_tx = -100;
				_ty = -100;
			}
			else if (_maxTrackTime < - (GAME_ONE_SECONED >> 1))
			{
				state = STATE::RANDMOVE;
				CGameBullet* shock = ProductFactory<CGameBullet>::Instance().GetProduct((int)CGameBullet::Type::effect_shock);
				shock->AddTarget("player");
				shock->SetXY(this->CenterX() - (shock->GetWidth() >> 1), this->CenterY() - (shock->GetHeight() >> 1));
				CGameObj::AddObj(shock);
			}
			break;
		}
		default:
			break;
		}

		int dx = (int)((double)Speed * _vector[0]), dy = (int)((double)Speed * _vector[1]);

		_mx += dx;

		if (CGameObj::Collision(map) || CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL))
		{
			_mx -= dx;
		}

		_my += dy;
		
		if (CGameObj::Collision(map) || CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL))
		{
			_my -= dy;
		}
		
		/*int ud = 0;

		if(abs(dx) > 0)
			ud = dx / abs(dx);

		_mx += dx;
		while (ud && (CGameObj::Collision(map) || CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL)))
		{
			_mx -= ud;
		}

		ud = 0;
		if (abs(dy) > 0)
			ud = dy / abs(dy);
		
		_my += dy;
		while (ud && (CGameObj::Collision(map) || CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL)))
		{
			_my -= ud;
		}*/
		
	}

	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	水晶礦
	CGameEnemy_Crystal::CGameEnemy_Crystal()
	{
		_hp = _maxHp = 60;
	}


	void CGameEnemy_Crystal::LoadBitmap()
	{
		_animaIter = GetAnima(CEnemy::Anima::RUN_R);
		_animaIter->AddBitmap(IDB_enemy_Crystal, RGB(255, 255, 255));


		_animaIter = GetAnima(CEnemy::Anima::RUN_L);
		_animaIter->AddBitmap(IDB_enemy_Crystal, RGB(255, 255, 255));


		_animaIter = GetAnima(CEnemy::Anima::DIE);
		_animaIter->AddBitmap(IDB_enemy_Crystal_die, RGB(255, 255, 255));

		*GetAnima(Anima::APPEARANCE) = CAnimationEnemyAppear::Instance();

		_animaIter = GetAnima(CEnemy::Anima::RUN_R);

	}


	void CGameEnemy_Crystal::OnMove(CGameMap* map)
	{
		if (!GetAnima(Anima::APPEARANCE)->IsFinalBitmap())
		{
			GetAnima(Anima::APPEARANCE)->OnMove();
		}
		_animaIter->OnMove();
	}

	void CGameEnemy_Crystal::Die()
	{
		_amountDie++;	// 敵人死亡數加一
		this->SetEnable(false);
		this->SetDie(true);
		this->SetCollision(false);
		this->SetShowPriority(0);
		_animaIter = GetAnima(CEnemy::Anima::DIE);
		// 隨機 DEAD 音效  CAudio::Instance()->Play(AUDIO_DEAD_ENEMY_0 + rand() % (AUDIO_DEAD_ENEMY_COUNT - AUDIO_DEAD_ENEMY_0));
		CAudio::Instance()->Play(AUDIO_DEAD_ENEMY_0);

		// 掉落能量球
		int t = 10 + rand() % 11;
		CGameObj* player = CCharacter::Instance();

		while (t--)
		{
			CGameTrackObj* obj = CGameTrackObj::CreateObj(1);
			obj->SetXY(this->CenterX(), this->CenterY());
			obj->SetTarget(player);
			CGameObj::AddObj(obj);
		}
		
	}

	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	金礦
	CGameEnemy_Gold::CGameEnemy_Gold()
	{
		_hp = _maxHp = 60;
	}


	void CGameEnemy_Gold::LoadBitmap()
	{
		_animaIter = GetAnima(CEnemy::Anima::RUN_R);
		_animaIter->AddBitmap(IDB_enemy_Gold, RGB(255, 255, 255));


		_animaIter = GetAnima(CEnemy::Anima::RUN_L);
		_animaIter->AddBitmap(IDB_enemy_Gold, RGB(255, 255, 255));


		_animaIter = GetAnima(CEnemy::Anima::DIE);
		_animaIter->AddBitmap(IDB_enemy_Gold_die, RGB(255, 255, 255));

		*GetAnima(Anima::APPEARANCE) = CAnimationEnemyAppear::Instance();

		_animaIter = GetAnima(CEnemy::Anima::RUN_R);

	}


	void CGameEnemy_Gold::OnMove(CGameMap* map) 
	{
		if (!GetAnima(Anima::APPEARANCE)->IsFinalBitmap())
		{
			GetAnima(Anima::APPEARANCE)->OnMove();
		}
		_animaIter->OnMove();
	}

	void CGameEnemy_Gold::Die()
	{
		_amountDie++;	// 敵人死亡數加一
		this->SetEnable(false);
		this->SetDie(true);
		this->SetCollision(false);
		this->SetShowPriority(0);
		_animaIter = GetAnima(CEnemy::Anima::DIE);
		// 隨機 DEAD 音效  CAudio::Instance()->Play(AUDIO_DEAD_ENEMY_0 + rand() % (AUDIO_DEAD_ENEMY_COUNT - AUDIO_DEAD_ENEMY_0));
		CAudio::Instance()->Play(AUDIO_DEAD_ENEMY_0);

		// 掉落金幣
		int t = 10 + rand() % 11;
		CGameObj* player = CCharacter::Instance();

		while (t--)
		{
			CGameTrackObj* obj = CGameTrackObj::CreateObj(0);
			obj->SetXY(this->CenterX(), this->CenterY());
			obj->SetTarget(player);
			CGameObj::AddObj(obj);
		}

	}

	/////////////////////////////////////////////////////////////////////////////
	
}