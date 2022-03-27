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
		_animas.reserve(AnimaSize);
		for(int i = 0; i < AnimaSize; i++)
			_animas.push_back(addAnima);
		this->Reset();
		this->SetXY(500, 500);
		
	}

	void CCharacter::Reset()
	{
		_animaIter = _animas.begin();
		_fire = false;
		free();
		_weapon.clear();
		_weapon.push_back(CGameWeapon());
		_nowWeapon = _weapon.begin();
		CCharacter::CGameObj::Reset();
		_vector[0] = 1;	//¹w³]´Â¥k
	}

	void CCharacter::free()
	{

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

		_nowWeapon->LoadBitmap();
	}

	void CCharacter::OnShow(CGameMap* map)
	{
		CCharacter::CGameObj::OnShow(map);
		_nowWeapon->OnShow(map);
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
			ModifyVector(0, -2);
			_mx -= _moveSpeed;
		}
		if (_isMovingRight)
		{
			ModifyVector(0, 2);
			_mx += _moveSpeed;
		}

		/*if ((_isMovingLeft || _isMovingRight) && !_isMovingUp && !_isMovingDown)
			ModifyVector(1, -_vector[1]);*/
		
		if (CCharacter::CGameObj::Collision(map))
			_mx = tempx;
		
		if (_isMovingUp)
		{
			ModifyVector(1, -2);
			_my -= _moveSpeed;
		}
		if (_isMovingDown)
		{
			ModifyVector(1, 2);
			_my += _moveSpeed;
		}

		/*if ((_isMovingUp || _isMovingDown) && !_isMovingLeft && !_isMovingRight)
			ModifyVector(0, -_vector[0]);*/

		if (CCharacter::CGameObj::Collision(map))
			_my = tempy;
		
		_nowWeapon->SetXY((GetX1() + GetX2()) >> 1, (GetY1() + GetY2()) >> 1);
		_nowWeapon->OnMove(map);
		if (_fire && _nowWeapon->isFire())
			_nowWeapon->Shoot(map, this);
		
	}

	void CCharacter::OnKeyUp(char nChar)
	{
		const char KEY_SPACE = 0x20;
		if (nChar == KEY_SPACE)
		{
			_fire = false;
		}

		CCharacter::CGameObj::OnKeyUp(nChar);
	}
	void CCharacter::OnKeyDown(char nChar)
	{
		const char KEY_SPACE = 0x20;
		if (nChar == KEY_SPACE)
		{
			_fire = true;
		}

		CCharacter::CGameObj::OnKeyDown(nChar);
	}

	void  CCharacter::ModifyVector(int index, int plus)
	{
		if (index > 1 || index < 0)
			return;
		_vector[index] += plus;
		if (_vector[index] > 1)
			_vector[index] = 1;
		else if (_vector[index] < -1)
			_vector[index] = -1;
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