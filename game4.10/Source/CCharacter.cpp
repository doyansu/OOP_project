#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"

namespace game_framework {
	CCharacter::CCharacter():_ATTDELAY(10)
	{
		//	動畫載入
		const int AnimaSize = 4;
		_animas.clear();
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation());

		//	屬性設定
		_hp = _maxHp = 6;
		_mp = _maxMp = 180;
		_shield = _maxShield = 5;
		_damage = 4;
		_showPriority = 10;
		this->Reset();
		this->SetXY(500, 500);
		this->SetTag("character");
		this->SetFree(false);

		//	武器載入
		_weapon.clear();
		_weapon.push_back(CGameWeapon());
		_nowWeapon = _weapon.begin();
	}

	void CCharacter::init()
	{
		
	}

	void CCharacter::Reset()
	{
		_doFire = false;
		_canAttack = true;
		_attCounter = 0;
		CCharacter::CGameObj::Reset();
		_vector[0] = 1;	//預設朝右
		DT = 1;
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
		//	動畫判斷
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
		//	動畫移動
		_animaIter->OnMove();

		//	角色移動、變更 vector 給子彈用
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

		if (CCharacter::CGameObj::Collision(map))
			_my = tempy;
		
		if ((_isMovingLeft != _isMovingRight) && !_isMovingDown  && !_isMovingUp && _vector[0] != 0)
			_vector[1] = 0;
		else if ((_isMovingDown != !_isMovingUp) && !_isMovingLeft && !_isMovingRight && _vector[1] != 0)
			_vector[0] = 0;
		
		
		//	武器移動
		_nowWeapon->DT_D(DT);
		if(DT)
			_nowWeapon->SetXY((GetX1() + GetX2()) >> 1, (GetY1() + GetY2()) >> 1);
		else
			_nowWeapon->SetXY(((GetX1() + GetX2()) >> 1) - (_nowWeapon->GetX2() - _nowWeapon->GetX1()), (GetY1() + GetY2()) >> 1);
		_nowWeapon->OnMove(map);
		
		//	武器射擊判斷
		if (_doFire)
		{
			const double MAXSEARCH = 600.0;	// 最大搜索範圍 
			const double MINSEARCH = 80.0;	// 最小搜索範圍 
			const double MAXMAPDISTANCE = 10000.0;	//	極限距離 玩家敵人間距離不超過
			// 找到存活的敵人
			vector<CGameObj*> enemys = CGameObjCenter::FindObjsBy(
				[](CGameObj* obj)
				{
					return obj->IsEnable() && obj->GetTag() == "enemy";
				}
			);
			// 找到最近的敵人
			double d = MAXMAPDISTANCE;
			CGameObj* target = nullptr;
			for (CGameObj* enemy : enemys)
			{
				if (d > this->Distance(enemy))
				{
					d = this->Distance(enemy);
					target = enemy;
				}
			}

			// 射擊
			if (_nowWeapon->CanFire() && target != nullptr && d >= MINSEARCH && d <= MAXSEARCH)// 找到敵人朝敵人射擊
			{
				double vx = (double)(target->CenterX() - this->CenterX()) / d;
				double vy = (double)(target->CenterY() - this->CenterY()) / d;
				_nowWeapon->Shoot(vx, vy);
			}
			else if(target != nullptr && _attCounter == 0 && Collision(target)) // 近戰攻擊
			{
				_attCounter = _ATTDELAY;
				target->TakeDmg(_damage);
			}
			else if (_nowWeapon->CanFire()) // 沒找到敵人朝 vector 射擊
			{
				_nowWeapon->Shoot(_vector[0], _vector[1]);
			}
		}

		//	計數
		if (_attCounter > 0)
			_attCounter--;
	}

	void CCharacter::OnKeyUp(char nChar)
	{
		//	Q 或 空白 射擊
		const char KEY_SPACE = 0x20;
		const char KEY_Q = 0x51;
		if (nChar == KEY_SPACE || nChar == KEY_Q)
		{
			_doFire = false;
		}

		CCharacter::CGameObj::OnKeyUp(nChar);
	}
	void CCharacter::OnKeyDown(char nChar)
	{
		//	Q 或 空白 射擊
		const char KEY_SPACE = 0x20;
		const char KEY_Q = 0x51;
		if (nChar == KEY_SPACE || nChar == KEY_Q)
		{
			_doFire = true;
		}

		CCharacter::CGameObj::OnKeyDown(nChar);
	}

	void CCharacter::TakeDmg(int dmg)
	{
		if (_shield)
		{
			_shield -= dmg;
			if (_shield < 0)
			{
				CGameObj::TakeDmg(-_shield);
			}
		}
		else
		{
			CGameObj::TakeDmg(dmg);
		}
	}

	void  CCharacter::ModifyVector(int index, int plus) //	調整向量範圍
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