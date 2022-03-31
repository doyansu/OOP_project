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
		// �ʵe���J
		_animas.clear();
		_animas.push_back(CAnimation());
		_animaIter = _animas.begin();

		// �ݩʳ]�w
		this->SetXY(400, 400);
		this->SetShowPriority(1);
		_hp = 10;
		CEnemy::CGameObj::SetTag("enemy");

		// �Z���]�w
		
	}

	void CEnemy::LoadBitmap()
	{
		_animaIter = GetAnima(CEnemy::Anima::INIT_R);
		_animaIter->AddBitmap(IDB_enemy0_0, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_3, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_4, RGB(255, 255, 255));

		_animaIter = _animas.begin();

		//_weapon.LoadBitmap();
	}

	void CEnemy::OnShow(CGameMap* map)
	{
		CEnemy::CGameObj::OnShow(map);
		//_weapon.OnShow(map);
	}

	void CEnemy::OnMove(CGameMap *map)
	{
		// �ĤH����
		const int randomRange = 20;	// �H���ܤ�V

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

		// �Z������
		//_weapon.SetXY(this->CenterX(), this->CenterY());
		//_weapon.OnMove(map);

		// �Z���g��
		/*if (_weapon.CanFire() && (rand() % randomRange) == 0)
		{
			CGameObj* player= CGameObjCenter::FindObjBy(
				[](CGameObj* obj)
				{
					return obj->GetTag() == "character";
				}
			);

			if (player)
			{
				double d = this->Distance(player);
				double vx = (double)(player->CenterX() - this->CenterX()) / d;
				double vy = (double)(player->CenterY() - this->CenterY()) / d;
				_weapon.Shoot(vx, vy);
			}
			
		}*/
	}

	void CEnemy::OnObjCollision(CGameObj* other)
	{
		/*if (other->GetTag() == "player")
			this->SetEnable(false);*/
	}

	void CEnemy::OnDie()
	{
		this->SetShowPriority(0);
	}



	vector<CAnimation>::iterator CEnemy::GetAnima(Anima type)
	{
		vector<CAnimation>::iterator anima = CEnemy::_animas.begin();
		switch (type)
		{
		case game_framework::CEnemy::Anima::INIT_R:
			anima = CEnemy::_animas.begin();
			break;
		default:
			break;
		}
		return anima;
	}
}