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
		//	�ʵe���J
		const int AnimaSize = 5;
		_animas.clear();
		_animas.reserve(AnimaSize);
		CAnimation animation;
		animation.SetDelayCount(3);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation(animation));

		//	�ݩʳ]�w
		_hp = _maxHp = 60000;
		_mp = _maxMp = 180;
		_shield = _maxShield = 5;
		_damage = 4;
		_moveSpeed = 20;
		_showPriority = 10;
		this->Reset();
		this->SetTag("player");
		this->SetFree(false);

		//	�Z���]�w
		_weapon.reserve(2);
		_weapon.push_back(CGameWeapon());
		_nowWeapon = _weapon.begin();
		_nowWeapon->SetTarget("enemy");
		_nowWeapon->SetAttributes(10, 0, 20, 3);
	}

	void CCharacter::Init()
	{
		// GameOver��l��
		_hp = 6;
		_mp = 180;
		_shield = 5;
		// ���m����l�Z��
		for (vector<CGameWeapon>::iterator it1 = _weapon.begin(); it1 != _weapon.end();)
		{
			it1 = _weapon.erase(it1);
		}
		_weapon.push_back(CGameWeapon());
		_nowWeapon = _weapon.begin();
		_nowWeapon->SetTarget("enemy");
		_nowWeapon->LoadBitmap();
	}

	void CCharacter::Reset()
	{
		_doFire = false;
		_canAttack = true;
		_attCounter = 0;
		_deathCounter = GAME_CYCLE_TIME * 2;	
		_shieldCounter = GAME_CYCLE_TIME;
		CCharacter::CGameObj::Reset();
		_vector[0] = 1;	//�w�]�¥k
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

		_animaIter = GetAnima(Anima::DIE);
		_animaIter->AddBitmap(IDB_CH1_DIE, RGB(255, 255, 255));

		_animaIter = _animas.begin();

		_nowWeapon->LoadBitmap();
	}

	void CCharacter::OnShow(CGameMap* map)
	{
		CCharacter::CGameObj::OnShow(map);
		if(!_isDie)
			_nowWeapon->OnShow(map);
	}

	void CCharacter::OnMove(CGameMap *map)
	{
		//	�ʵe����
		_animaIter->OnMove();

		//	�ʵe�P�_
		if (_isMovingRight) 
			DT = 1;
		else if (_isMovingLeft) 
			DT = 0;
		
		if (this->IsMoveing())
		{
			if (DT)
				_animaIter = GetAnima(Anima::RUN_R);
			else
				_animaIter = GetAnima(Anima::RUN_L);
		}
		else if (DT)
			_animaIter = GetAnima(Anima::INIT_R);
		else
			_animaIter = GetAnima(Anima::INIT_L);
				

		//	���Ⲿ��
		int tempx = _mx, tempy = _my;
		if (_isMovingLeft)
		{
			_mx -= _moveSpeed;
		}
		if (_isMovingRight)
		{
			_mx += _moveSpeed;
		}
		
		if (CCharacter::CGameObj::Collision(map))
			_mx = tempx;
		
		if (_isMovingUp)
		{
			_my -= _moveSpeed;
		}
		if (_isMovingDown)
		{
			_my += _moveSpeed;
		}

		if (CCharacter::CGameObj::Collision(map))
			_my = tempy;
		

		//�ܧ� vector ���l�u��
		if(!(_isMovingUp && _isMovingDown) && !_isMovingLeft && _isMovingRight)
			_vector[0] = 1;
		else if(!(_isMovingUp && _isMovingDown) && _isMovingLeft && !_isMovingRight)
			_vector[0] = -1;
		else if((_isMovingUp ^ _isMovingDown) && !_isMovingLeft && !_isMovingRight)
			_vector[0] = 0;

		if (!_isMovingUp && _isMovingDown && !(_isMovingLeft && _isMovingRight))
			_vector[1] = 1;
		else if (_isMovingUp && !_isMovingDown && !(_isMovingLeft && _isMovingRight))
			_vector[1] = -1;
		else if (!_isMovingUp && !_isMovingDown && (_isMovingLeft ^ _isMovingRight))
			_vector[1] = 0;
		/*if ((_isMovingLeft != _isMovingRight) && !_isMovingDown  && !_isMovingUp && _vector[0] != 0)
			_vector[1] = 0;
		else if ((_isMovingDown != !_isMovingUp) && !_isMovingLeft && !_isMovingRight && _vector[1] != 0)
			_vector[0] = 0;*/

		//	�Z������
		_nowWeapon->OnMove(map);
		_nowWeapon->SetDT(DT);
		if(DT)
			_nowWeapon->SetXY(this->CenterX(), this->CenterY());
		else 
			_nowWeapon->SetXY(this->CenterX() - (_nowWeapon->GetX2() - _nowWeapon->GetX1()), this->CenterY());

		//	�Z���g���P�_
		if (_doFire)
		{
			const double MAXSEARCH = 500.0;	// �̤j�j���d�� 
			const double MINSEARCH = 80.0;	// �̤p�j���d�� 
			// ���s�����ĤH
			vector<CGameObj*> enemys = CGameObjCenter::FindObjsBy(
				[](CGameObj* obj)
				{
					return obj->IsEnable() && obj->GetTag() == "enemy";
				}
			);
			// ���̪񪺼ĤH
			double d = MAXSEARCH;
			CGameObj* target = nullptr;
			for (CGameObj* enemy : enemys)
			{
				if (d > this->Distance(enemy))
				{
					d = this->Distance(enemy);
					target = enemy;
				}
			}

			// �g�����ܧ󨤦�B�Z���¦V
			if (target != nullptr && d <= MAXSEARCH)
			{
				if (target->CenterX() - this->CenterX() > 0)
				{
					_nowWeapon->SetDT(1);
					_nowWeapon->SetXY(this->CenterX(), this->CenterY()); 
					if (this->IsMoveing())
						_animaIter = GetAnima(Anima::RUN_R);
					else
						_animaIter = GetAnima(Anima::INIT_R);
				}
				else
				{
					_nowWeapon->SetDT(0);
					_nowWeapon->SetXY(this->CenterX() - (_nowWeapon->GetX2() - _nowWeapon->GetX1()), this->CenterY());
					if(this->IsMoveing())
						_animaIter = GetAnima(Anima::RUN_L);
					else 
						_animaIter = GetAnima(Anima::INIT_L);
				}	
			}

			// �g��
			if (_nowWeapon->CanFire() && target != nullptr && d >= MINSEARCH && d <= MAXSEARCH)// ���ĤH�¼ĤH�g��
			{
				double vx = (double)(target->CenterX() - this->CenterX()) / d;
				double vy = (double)(target->CenterY() - this->CenterY()) / d;
				_nowWeapon->Shoot(vx, vy);
			}
			else if(target != nullptr && _attCounter == 0 && d < MINSEARCH) // ��ԧ���
			{
				_attCounter = _ATTDELAY;
				target->TakeDmg(_damage);
			}
			else if (_nowWeapon->CanFire()) // �S���ĤH�� vector �g��
			{
				_nowWeapon->Shoot(_vector[0], _vector[1]);
			}
		}
		

		// ��ԧ����p��
		if (_attCounter > 0)
			_attCounter--;
		// �@�y�p��
		if (--_shieldCounter == 0)
		{
			_shieldCounter = GAME_CYCLE_TIME;
			ModifyShield(1);
		}
			
	}

	void CCharacter::OnDie()
	{
		_animaIter = GetAnima(CCharacter::Anima::DIE);
		_animaIter->OnMove();
		// ���`�˼�
		if(--_deathCounter == 0)
			this->SetDie(false);
	}

	void CCharacter::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		/*if (other->GetTag() == "enemy")
		{
			other->SetVector(other->GetVectorX() + this->GetVectorX(), other->GetVectorY() + this->GetVectorY());
		}*/
	}

	void CCharacter::OnKeyUp(char nChar)
	{
		//	Q �� �ť� �g��
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
		//	Q �� �ť� �g��
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
		_shieldCounter = GAME_CYCLE_TIME * 5; // 5��
		if (_shield)
		{
			_shield -= dmg;
			if (_shield < 0)
			{
				CGameObj::TakeDmg(-_shield);
				_shield = 0;
			}
		}
		else
		{
			CGameObj::TakeDmg(dmg);
		}
	}
	void CCharacter::ModifyShield(int add)
	{
		_shield += add;
		if (_shield > _maxShield)
			_shield = _maxShield;
	}

	void  CCharacter::ModifyVector(int index, int plus) //	�վ�V�q�d�� �S�ΤW
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
		case game_framework::CCharacter::Anima::DIE:
			anima = _animas.begin() + 4;
			break;
		default:
			break;
		}
		return anima;
	}

	int CCharacter::GetHP()
	{
		return _hp;
	}

	int CCharacter::GetMAXHP()
	{
		return _maxHp;
	}

	int CCharacter::GetMP()
	{
		return _mp;
	}

	int CCharacter::GetMAXMP()
	{
		return _maxMp;
	}

	int CCharacter::GetShield() 
	{
		return _shield;
	}

	int CCharacter::GetMAXShield()
	{
		return _maxShield;
	}
	

}