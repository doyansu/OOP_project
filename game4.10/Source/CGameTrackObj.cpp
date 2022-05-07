#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameTrackObj.h"

namespace game_framework
{
	CGameTrackObj::CGameTrackObj(TYPE type)
	{
		//	屬性設定
		_target = nullptr;
		_type = type;

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
	}


	void CGameTrackObj::OnObjCollision(CGameMap*, CGameObj*)
	{

	}

	void CGameTrackObj::OnDie(CGameMap*)
	{

	}
}
