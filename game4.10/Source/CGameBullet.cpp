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
		_mx += (int)((double)_moveSpeed * _vector[0]);
		_my += (int)((double)_moveSpeed * _vector[1]);

		//	接觸到地圖圍牆停止或房間通道連接處
		if (CGameBullet::CGameObj::Collision(map) || CGameBullet::CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL))
			CGameBullet::CGameObj::SetEnable(false);
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

}
