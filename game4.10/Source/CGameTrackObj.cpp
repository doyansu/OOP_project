#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameTrackObj.h"

namespace game_framework
{
	CGameTrackObj CGameTrackObj::_trackObjs[(int)TYPE::TYPECOUNT];

	CGameTrackObj::CGameTrackObj(TYPE type)
	{
		//	屬性設定
		_target = nullptr;
		_type = type;
		_counter = GAME_ONE_SECONED;
		_isCollision = false;

		//	平移距離
		double x = -10 + rand() % 20, y = -10 + rand() % 20;
		double d = 2 * sqrt((double)(x * x + y * y));
		_vector[0] = x / d;
		_vector[1] = y / d;

		if (type == TYPE::GOLD)
		{
			_tag = "gold";
		}
		else
		{
			_tag = "energyball";
		}

		//	動畫設定
		_animas.push_back(CAnimation());
	}

	void CGameTrackObj::LoadBitmap()
	{
		_animaIter = _animas.begin();
		switch (_type)
		{
		case game_framework::CGameTrackObj::TYPE::GOLD:
			_animaIter->AddBitmap(IDB_gold_1_0, RGB(255, 255, 255));
			_animaIter->AddBitmap(IDB_gold_1_1, RGB(255, 255, 255));
			_animaIter->AddBitmap(IDB_gold_1_2, RGB(255, 255, 255));
			_animaIter->AddBitmap(IDB_gold_1_3, RGB(255, 255, 255));
			break;
		case game_framework::CGameTrackObj::TYPE::ENERGYBALL:
			_animaIter->AddBitmap(IDB_energyBall_0, RGB(255, 255, 255));
			break;
		default:
			break;
		}
	}

	void CGameTrackObj::OnMove(CGameMap*)
	{
		_animaIter->OnMove();

		if (_target == nullptr)
		{
			return;
		}

		if (_counter > 0)
		{
			_counter--;
			if (_counter > (GAME_ONE_SECONED >> 1))
			{
				_mx += (int)(10 * _vector[0]);
				_my += (int)(10 * _vector[1]);
			}
		}
		else
		{
			Die();
			_isCollision = true;
		}
		
	}

	void CGameTrackObj::OnDie(CGameMap*)
	{
		_animaIter->OnMove();
		if (_target == nullptr)
		{
			return;
		}

		double d = this->Distance(_target);
		const int maxd = 250;				//	搜索距離
		if (d < maxd)
		{
			double vx = (double)(_target->CenterX() - this->CenterX()) / d;
			double vy = (double)(_target->CenterY() - this->CenterY()) / d;
			_mx += (int)((double)_moveSpeed * vx);
			_my += (int)((double)_moveSpeed * vy);
		}
	}

	void CGameTrackObj::OnObjCollision(CGameMap*, CGameObj* other)
	{
		if (other->GetTag() == "player")
		{
			this->SetDie(false);
		}
	}

	void CGameTrackObj::SetTarget(CGameObj* target)
	{
		_target = target;
		_moveSpeed = _target->GetMoveSpeed();
	}
}
