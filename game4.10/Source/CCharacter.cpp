#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"

namespace game_framework {
	CCharacter::CCharacter()
	{
		init();
	}

	void CCharacter::init()
	{
		const int AnimaSize = 4;
		CAnimation addAnima;
		_animas.clear();
		for(int i = 0; i < AnimaSize; i++)
			_animas.push_back(addAnima);

		this->Reset();
		this->SetXY(500, 500);
		
	}

	void CCharacter::Reset()
	{
		_animaIter = _animas.begin();
		CGameObj::Reset();
	}

	void CCharacter::LoadBitmap()
	{
		_animaIter = GetAnima(Anima::INIT_L);
		_animaIter->AddBitmap(IDB_CH1_4_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_5_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_6_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_7_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_6_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_5_L, RGB(255, 255, 255));

		_animaIter = GetAnima(Anima::INIT_R);
		_animaIter->AddBitmap(IDB_CH1_4, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_5, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_6, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_7, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_6, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_5, RGB(255, 255, 255));

		_animaIter = GetAnima(Anima::RUN_R);
		_animaIter->AddBitmap(IDB_CH1_0, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_3, RGB(255, 255, 255));

		_animaIter = GetAnima(Anima::RUN_L);
		_animaIter->AddBitmap(IDB_CH1_0_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_1_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_2_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_3_L, RGB(255, 255, 255));

		_animaIter = _animas.begin();
	}

	void CCharacter::OnShow(CGameMap* map)
	{
		CGameObj::OnShow(map);
	}

	void CCharacter::OnMove(CGameMap *map)
	{
		if (_isMovingRight) {
			_animaIter = GetAnima(Anima::RUN_R);
			DT = 1;
		} else if (_isMovingLeft) {
			_animaIter = GetAnima(Anima::RUN_L);
			DT = 0;
		} else if (DT && (_isMovingDown || _isMovingUp))
			_animaIter = GetAnima(Anima::RUN_R);
		else if (!DT && (_isMovingDown || _isMovingUp))
			_animaIter = GetAnima(Anima::RUN_L);
		else
			if (DT)
				_animaIter = GetAnima(Anima::INIT_R);
			else
				_animaIter = GetAnima(Anima::INIT_L);
		_animaIter->OnMove();

		int x1 = GetX1();
		int y1 = GetY1();
		int x2 = GetX2();
		int y2 = GetY2();
		
		if (_isMovingLeft) 
		{
			if (map->IsEmpty(x1 - _moveSpeed, y1) && map->IsEmpty(x1 - _moveSpeed, y2) && map->IsEmpty(x2 - _moveSpeed, y1) && map->IsEmpty(x2 - _moveSpeed, y2))
				_mx -= _moveSpeed;
		}
				
		if (_isMovingRight)
		{
			if (map->IsEmpty(x1 + _moveSpeed, y1) && map->IsEmpty(x1 + _moveSpeed, y2) && map->IsEmpty(x2 + _moveSpeed, y1) && map->IsEmpty(x2 + _moveSpeed, y2))
				_mx += _moveSpeed;
		}
			
		if (_isMovingUp)
		{
			if (map->IsEmpty(x1, y1 - _moveSpeed) && map->IsEmpty(x1, y2 - _moveSpeed) && map->IsEmpty(x2, y1 - _moveSpeed) && map->IsEmpty(x2, y2 - _moveSpeed))
				_my -= _moveSpeed;
		}
			
		if (_isMovingDown)
		{
			if (map->IsEmpty(x1, y1 + _moveSpeed) && map->IsEmpty(x1, y2 + _moveSpeed) && map->IsEmpty(x2, y1 + _moveSpeed) && map->IsEmpty(x2, y2 + _moveSpeed))
				_my += _moveSpeed;
		}
			
		
	}

	vector<CAnimation>::iterator CCharacter::GetAnima(Anima type)
	{
		vector<CAnimation>::iterator anima = _animas.begin();
		switch (type)
		{
		case game_framework::CCharacter::Anima::INIT_R:
			anima = _animas.begin();
			break;
		case game_framework::CCharacter::Anima::INIT_L:
			anima = _animas.begin() + 1;
			break;
		case game_framework::CCharacter::Anima::RUN_R:
			anima = _animas.begin() + 2;
			break;
		case game_framework::CCharacter::Anima::RUN_L:
			anima = _animas.begin() + 3;
			break;
		default:
			break;
		}
		return anima;
	}
}