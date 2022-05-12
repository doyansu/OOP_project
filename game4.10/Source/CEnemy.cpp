#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEnemy.h"
#include "CGameObjCenter.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEnemy: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEnemy::CEnemy()
	{
		// 動畫載入
		const int AnimaSize = 3;
		_animas.clear();
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation());

		// 屬性設定
		this->SetXY(400, 400);
		this->SetShowPriority(1);
		this->_hp = 10;
		this->_moveSpeed = 3;
		CEnemy::CGameObj::SetTag("enemy");

		// 武器設定
		_weapon = new CGameWeapon(this);
		_weapon->SetAttributes(1, 0, 5, 50);
		_weapon->SetTarget("player");
	}

	CEnemy::~CEnemy()
	{
		free();
	}

	CEnemy::CEnemy(const CEnemy& other):CGameObj(other)
	{
		copy(other);
	}

	/*CEnemy& CEnemy::operator=(const CEnemy& other)
	{
		if (this != &other)
		{
			free();
			copy(other);
		}
		return *this;
	}*/

	void CEnemy::copy(const CEnemy& other)
	{
		_weapon = new CGameWeapon(*(other._weapon));
		_weapon->SetUser(this);
	}

	void CEnemy::free()
	{
		delete _weapon;
		_weapon = nullptr;
	}

	void CEnemy::LoadBitmap()
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

		_animaIter = _animas.begin();

		_weapon->LoadBitmap();
	}

	void CEnemy::OnShow(CGameMap* map)
	{
		CEnemy::CGameObj::OnShow(map);
		if(!_isDie)
			_weapon->OnShow(map);
	}

	void CEnemy::OnMove(CGameMap *map)
	{
		// 敵人移動
		const int randomRange = 20;	// 隨機變方向

		if ((rand() % randomRange) == 0)
		{
			_vector[0] = -(_moveSpeed) + (rand() % ((_moveSpeed << 1) + 1));
			_vector[1] = -(_moveSpeed) + (rand() % ((_moveSpeed << 1) + 1));
		}

		_animaIter->OnMove();
		_mx += (int)_vector[0];
		_my += (int)_vector[1];

		if (CGameObj::Collision(map) || CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL))
		{
			_mx -= (int)_vector[0];
			_my -= (int)_vector[1];
		}

		// 武器移動
		_weapon->SetCenter(this->CenterX(), this->CenterY());
		_weapon->OnMove(map);
		
		// 武器射擊
		if (_weapon->CanFire() && (rand() % 10 == 0))
		{
			/*CGameObj* player= CGameTool::FindObjBy(CGameObj::_allObj,
				[](CGameObj* obj)
				{
					return obj->GetTag() == "player";
				}
			);*/

			CGameObj* player = CCharacter::_nowPlayer;

			const double MAXSEARCH = 300.0;	// 最大搜索範圍
			if (player)
			{
				double d = this->Distance(player);
				double vx = (double)(player->CenterX() - this->CenterX()) / d;
				double vy = (double)(player->CenterY() - this->CenterY()) / d;
				if (d <= MAXSEARCH)
					_weapon->Shoot(vx, vy);

				// 切換動畫
				if (vx > 0)
				{
					_animaIter = GetAnima(CEnemy::Anima::RUN_R);	
					_weapon->SetDT(1);
				}
				else
				{
					_animaIter = GetAnima(CEnemy::Anima::RUN_L);
					_weapon->SetDT(0);
				}
					
			}
		}
	}

	void CEnemy::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		/*if (other->GetTag() == "player")
		{
			double vx = _vector[0], vy = _vector[1];
			_vector[0] += other->GetVectorX();
			_vector[1] += other->GetVectorY();
			if (abs(_vector[0]) > 5)
				_vector[0] = vx;
			if (abs(_vector[1]) > 5)
				_vector[1] = vy;
		}*/
	}

	void CEnemy::Die()
	{
		this->SetEnable(false);
		this->SetDie(true);
		this->SetCollision(false);
		this->SetShowPriority(0);
		_animaIter = GetAnima(CEnemy::Anima::DIE);

		if (rand() % 10 < 2)	//	20 % 掉落金幣或能量球
		{
			int t = 1 + rand() % 3;
			CGameObj* player = CGameTool::FindObjBy(CGameObj::_allObj,
				[](CGameObj* obj)
			{
				return obj->GetTag() == "player";
			});
			while (t--)
			{
				int r = rand() % 2;
				CGameTrackObj* obj = CGameTrackObj::CreateObj(r);
				obj->SetXY(this->CenterX(), this->CenterY());
				obj->SetTarget(player);
				CGameObj::AddObj(obj);
			}
		}
	}

	void CEnemy::OnDie(CGameMap* map)
	{
		_animaIter->OnMove();
	}

	vector<CAnimation>::iterator CEnemy::GetAnima(Anima type)
	{
		return _animas.begin() + (int)type;
	}
}