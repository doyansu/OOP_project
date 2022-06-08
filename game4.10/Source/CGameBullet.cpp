#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameBullet.h"

namespace game_framework
{
	CGameBullet::CGameBullet()
	{
		_showPriority = 5;
		_damage = 4;
		_bulletType = Type::INIT;
		_survive = 60 * GAME_ONE_SECONED;
		this->SetTag("bullet");
	}

	/*CGameBullet::CGameBullet(const CGameBullet& other):CGameObj(other)
	{
		_damage = other._damage;
		_target = other._target;
	}*/


	void CGameBullet::OnMove(CGameMap* map)
	{
		//	根據 _vector 進行移動
		double Speed = _moveSpeed;
		double dx = Speed * _vector[0];
		double dy = Speed * _vector[1];
		_moveTarget[0] += dx;
		_moveTarget[1] += dy;
		_mx = (int)_moveTarget[0];
		_my = (int)_moveTarget[1];

		//	存活時間過去會消失
		_survive--;
		if (_survive < 0)
		{
			Die();
		}

		//	接觸到地圖圍牆停止或房間通道連接處
		if (CGameBullet::CGameObj::Collision(map) || CGameBullet::CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL))
			Die();
	}

	void CGameBullet::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		for (string target : _targets)
		{
			if (other->GetTag() == target)
			{
				other->TakeDmg(_damage);
				this->Die();
				break;
			}
		}
		
	}

	void CGameBullet::Die()
	{
		this->SetEnable(false);
		this->SetCollision(false);
		this->SetDie(true);
	}

	void CGameBullet::OnDie(CGameMap*)
	{
		//	動畫播完再釋放
		if (!_animaIter->IsFinalBitmap())
		{
			_animaIter->OnMove();
		}
		else
		{
			this->SetDie(false);
		}
	}

	void CGameBullet::AddTarget(string target)
	{
		_targets.push_back(target);
	}

	void CGameBullet::SetDamage(int damage)
	{
		_damage = damage;
	}

	void CGameBullet::SetSurvive(int value)
	{
		_survive = value;
	}

}
