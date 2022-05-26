#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameInteractOnceObj.h"

namespace game_framework
{

	CGameInteractOnceObj::CGameInteractOnceObj(Type type)
	{
		const int AnimaSize = (int)Anima::ANIMACOUNT;
		_animas.clear();
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation());

		_collPlayer = false;
		this->_type = type;
		switch (type)
		{
		case game_framework::CGameInteractOnceObj::Type::REDPOTION:
			this->SetTag("redpotion");
			break;
		case game_framework::CGameInteractOnceObj::Type::BIGREDPOTION:
			this->SetTag("bigredpotion");
			break;
		case game_framework::CGameInteractOnceObj::Type::BULEPOTION:
			this->SetTag("bulepotion");
			break;
		case game_framework::CGameInteractOnceObj::Type::BIGBULEPOTION:
			this->SetTag("bigbulepotion");
			break;
		default:
			this->SetTag("error");
			break;
		}
	}

	int CGameInteractOnceObj::GetX2()
	{
		return _mx + GetAnima(Anima::MAIN)->Width();
	}
	int CGameInteractOnceObj::GetY2()
	{
		return _my + GetAnima(Anima::MAIN)->Height();
	}
	int CGameInteractOnceObj::Width()
	{
		return GetAnima(Anima::MAIN)->Width();
	}
	int CGameInteractOnceObj::Height()
	{
		return GetAnima(Anima::MAIN)->Height();
	}

	void CGameInteractOnceObj::LoadBitmap()
	{
		_animaIter = GetAnima(Anima::MAIN);

		switch (_type)
		{
		case game_framework::CGameInteractOnceObj::Type::REDPOTION:
			_animaIter->AddBitmap(IDB_REDPOTION_0, RGB(255, 255, 255));
			break;
		case game_framework::CGameInteractOnceObj::Type::BIGREDPOTION:
			_animaIter->AddBitmap(IDB_REDPOTION_1, RGB(255, 255, 255));
			break;
		case game_framework::CGameInteractOnceObj::Type::BULEPOTION:
			_animaIter->AddBitmap(IDB_BULEPOTION_0, RGB(255, 255, 255));
			break;
		case game_framework::CGameInteractOnceObj::Type::BIGBULEPOTION:
			_animaIter->AddBitmap(IDB_BULEPOTION_1, RGB(255, 255, 255));
			break;
		default:
			_animaIter->AddBitmap(IDB_ItemArrow_0, RGB(0, 0, 0));
			break;
		}

		*GetAnima(Anima::ARROW) = CGameArrow::Instance();
	}
	void CGameInteractOnceObj::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		if (!_collPlayer && other->GetTag() == "player")
		{
			_collPlayer = true;
		}
	}
	void CGameInteractOnceObj::Die()
	{
		this->SetEnable(false);
		this->SetDie(false);
	}

	void CGameInteractOnceObj::OnMove(CGameMap* map)
	{
		if (_collPlayer)
		{
			GetAnima(Anima::ARROW)->OnMove();
			_collPlayer = false;
		}
		else // 重製動畫
		{
			GetAnima(Anima::ARROW)->Reset();
		}

	}
	void CGameInteractOnceObj::OnShow(CGameMap* map)
	{
		_animaIter = GetAnima(Anima::MAIN);
		_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));
		_animaIter->OnShow();

		if (_collPlayer)
		{
			_animaIter = GetAnima(Anima::ARROW);
			_animaIter->SetTopLeft(map->ScreenX(_mx + ((GetAnima(Anima::MAIN)->Width() - _animaIter->Width()) >> 1)),
				map->ScreenY(_my - _animaIter->Height()));
			_animaIter->OnShow();
		}
	}

	vector<CAnimation>::iterator CGameInteractOnceObj::GetAnima(Anima type)
	{
		return _animas.begin() + (int)type;
	}
}