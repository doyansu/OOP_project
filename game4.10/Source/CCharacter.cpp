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

	CCharacter::~CCharacter()
	{
		free();
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
		free();
		_weapon.clear();
		_weapon.push_back(new CGameWeapon());
		_nowWeapon = _weapon.begin();
		CGameObj::Reset();
	}

	void CCharacter::free()
	{
		for (CGameObj *p : _weapon)
			delete p;
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

		(*_nowWeapon)->LoadBitmap();
	}

	void CCharacter::OnShow(CGameMap* map)
	{
		CGameObj::OnShow(map);
		(*_nowWeapon)->OnShow(map);
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

		int tempx = _mx, tempy = _my;
		if (_isMovingLeft)
		{
			_mx -= _moveSpeed;
		}
		if (_isMovingRight)
		{
			_mx += _moveSpeed;
		}
		if (CGameObj::Collision(map))
			_mx = tempx;
		
		if (_isMovingUp)
		{
			_my -= _moveSpeed;
		}
		if (_isMovingDown)
		{
			_my += _moveSpeed;
		}

		if (CGameObj::Collision(map))
			_my = tempy;
		
		(*_nowWeapon)->SetXY((GetX1() + GetX2()) >> 1, (GetY1() + GetY2()) >> 1);
		
	}

	void CCharacter::Shoot()
	{
		(*_nowWeapon)->ObjFuntion(this);
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