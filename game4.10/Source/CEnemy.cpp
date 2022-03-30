#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEnemy.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEnemy: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEnemy::CEnemy()
	{
		Initialize();
	}

	void CEnemy::Initialize()
	{
		this->SetXY(400, 400);
		//_animas.clear();
		//_animas.push_back(CAnimation());
		_animaIter = _animas.begin();
		CEnemy::CGameObj::SetTag("enemy");
	}

	void CEnemy::LoadBitmap()
	{
		_animas.at(0).AddBitmap(IDB_enemy0_0, RGB(255, 255, 255));
		_animas.at(0).AddBitmap(IDB_enemy0_1, RGB(255, 255, 255));
		_animas.at(0).AddBitmap(IDB_enemy0_2, RGB(255, 255, 255));
		_animas.at(0).AddBitmap(IDB_enemy0_3, RGB(255, 255, 255));
		_animas.at(0).AddBitmap(IDB_enemy0_4, RGB(255, 255, 255));
		_animaIter = _animas.begin();
	}

	/*void CEnemy::OnShow(CGameMap* map)
	{
		CEnemy::CGameObj::OnShow(map);
	}*/

	void CEnemy::OnMove(CGameMap *map)
	{
		CEnemy::_animaIter = GetAnima(Anima::INIT_R);
		CEnemy::CGameObj::EnemyOnMove(map);
	}

	void CEnemy::OnObjCollision(CGameObj* other)
	{
		if (other->GetTag() == "player")
			this->SetEnable(false);
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