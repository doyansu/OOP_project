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
		const int AnimaSize = 2;
		_animas.clear();
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation());

		// 屬性設定
		this->SetXY(400, 400);
		this->SetShowPriority(1);
		_hp = 10;
		CEnemy::CGameObj::SetTag("enemy");

		// 武器設定
		_weapon.SetUser(this);
		_weapon.SetAttributes(1, 0, 5, 50);
	}

	void CEnemy::LoadBitmap()
	{
		_animaIter = GetAnima(CEnemy::Anima::INIT_R);
		_animaIter->AddBitmap(IDB_enemy0_0, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_3, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_4, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::DIE);
		_animaIter->AddBitmap(IDB_enemy0_die, RGB(255, 255, 255));

		_animaIter = _animas.begin();

		_weapon.LoadBitmap();
	}

	void CEnemy::OnShow(CGameMap* map)
	{
		CEnemy::CGameObj::OnShow(map);
		if(!_isDie)
			_weapon.OnShow(map);
	}

	void CEnemy::OnMove(CGameMap *map)
	{
		// 敵人移動
		const int randomRange = 20;	// 隨機變方向

		_animaIter->OnMove();
		_mx += (int)_vector[0];
		_my += (int)_vector[1];

		if (CGameObj::Collision(map))
		{
			_mx -= (int)_vector[0];
			_my -= (int)_vector[1];
		}

		if ((rand() % randomRange) == 0)
		{
			_vector[0] = -(_moveSpeed >> 1) + (rand() % _moveSpeed);
			_vector[1] = -(_moveSpeed >> 1) + (rand() % _moveSpeed);
		}

		// 武器移動
		_weapon.SetXY(this->CenterX(), this->CenterY());
		_weapon.OnMove(map);

		// 武器射擊
		if (_weapon.CanFire())
		{
			CGameObj* player= CGameObjCenter::FindObjBy(
				[](CGameObj* obj)
				{
					return obj->GetTag() == "player";
				}
			);

			if (player)
			{
				double d = this->Distance(player);
				double vx = (double)(player->CenterX() - this->CenterX()) / d;
				double vy = (double)(player->CenterY() - this->CenterY()) / d;
				_weapon.Shoot(vx, vy);
			}
			
		}
	}

	void CEnemy::OnObjCollision(CGameObj* other)
	{
		/*if (other->GetTag() == "player")
			this->SetEnable(false);*/
	}

	void CEnemy::OnDie()
	{
		this->SetShowPriority(0);
		_animaIter = GetAnima(CEnemy::Anima::DIE);
		_animaIter->OnMove();
	}



	vector<CAnimation>::iterator CEnemy::GetAnima(Anima type)
	{
		vector<CAnimation>::iterator anima = CEnemy::_animas.begin();
		switch (type)
		{
		case game_framework::CEnemy::Anima::INIT_R:
			anima = CEnemy::_animas.begin();
			break;
		case game_framework::CEnemy::Anima::DIE:
			anima = CEnemy::_animas.begin() + 1;
			break;
		default:
			break;
		}
		return anima;
	}
}