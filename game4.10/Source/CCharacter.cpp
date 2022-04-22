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
		const int AnimaSize = 5;
		_animas.clear();
		_animas.reserve(AnimaSize);
		CAnimation animation;
		animation.SetDelayCount(3);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation(animation));

		//	屬性設定
		_hp = _maxHp = 20;
		_mp = _maxMp = 180;
		_shield = _maxShield = 10;
		_damage = 4;
		_moveSpeed = 20;
		_showPriority = 10;
		this->Reset();
		this->SetTag("player");
		this->SetFree(false);

		//	武器設定
		_weapons[0] = new CGameWeapon(this);
		_weapons[1] = nullptr;
		_nowWeapon = &_weapons[0];
		(*_nowWeapon)->SetTarget("enemy");
		(*_nowWeapon)->SetAttributes(10, 0, 20, 3);
	}

	void CCharacter::Init()
	{
		// GameOver初始化
		_hp = 6;
		_mp = 180;
		_shield = 5;
		// 重置為初始武器
		free();
		_weapons[0] = new CGameWeapon(this);
		_weapons[1] = nullptr;
		_nowWeapon = &_weapons[0];
		(*_nowWeapon)->LoadBitmap();
		(*_nowWeapon)->SetTarget("enemy");
		(*_nowWeapon)->SetAttributes(10, 0, 20, 3);
	}

	void CCharacter::Reset()
	{
		_doFire = false;
		_canAttack = true;
		_attCounter = 0;
		_deathCounter = GAME_CYCLE_TIME * 2;	
		_shieldCounter = GAME_CYCLE_TIME;
		CCharacter::CGameObj::Reset();
		_vector[0] = 1;	//預設朝右
		DT = 1;
	}

	CCharacter::~CCharacter()
	{
		free();
	}

	void CCharacter::free()
	{
		if (_weapons[0] != nullptr)
			delete _weapons[0];
		if (_weapons[1] != nullptr)
			delete _weapons[1];
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

		(*_nowWeapon)->LoadBitmap();
	}

	void CCharacter::OnShow(CGameMap* map)
	{
		CCharacter::CGameObj::OnShow(map);
		if(!_isDie)
			(*_nowWeapon)->OnShow(map);
	}

	void CCharacter::OnMove(CGameMap *map)
	{
		//	動畫移動
		_animaIter->OnMove();

		//	動畫判斷
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
				

		//	角色移動
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
		

		//變更 vector 給子彈用
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

		//	武器移動
		(*_nowWeapon)->OnMove(map);
		(*_nowWeapon)->SetDT(DT);
		/*if(DT)
			_nowWeapon->SetXY(this->CenterX(), this->CenterY());
		else 
			_nowWeapon->SetXY(this->CenterX() - (_nowWeapon->GetX2() - _nowWeapon->GetX1()), this->CenterY());*/

		//	武器射擊判斷
		if (_doFire)
		{
			const double MAXSEARCH = 500.0;	// 最大搜索範圍 
			const double MINSEARCH = 80.0;	// 最小搜索範圍 
			// 找到存活的敵人
			vector<CGameObj*> enemys = CGameObjCenter::FindObjsBy(
				[](CGameObj* obj)
				{
					return obj->IsEnable() && obj->GetTag() == "enemy";
				}
			);
			// 找到最近的敵人
			double d = MAXSEARCH;
			CGameObj* target = nullptr;
			for (CGameObj* enemy : enemys)
			{
				double ed = this->Distance(enemy);
				if (d > ed && ed > MINSEARCH && !hasObstacle(map, this, enemy))
				{
					d = ed;
					target = enemy;
				}
			}

			// 射擊時變更角色、武器朝向
			if (target != nullptr && d <= MAXSEARCH)
			{
				if (target->CenterX() - this->CenterX() > 0)
				{
					(*_nowWeapon)->SetDT(1);
					//_nowWeapon->SetXY(this->CenterX(), this->CenterY()); 
					if (this->IsMoveing())
						_animaIter = GetAnima(Anima::RUN_R);
					else
						_animaIter = GetAnima(Anima::INIT_R);
				}
				else
				{
					(*_nowWeapon)->SetDT(0);
					//_nowWeapon->SetXY(this->CenterX() - (_nowWeapon->GetX2() - _nowWeapon->GetX1()), this->CenterY());
					if(this->IsMoveing())
						_animaIter = GetAnima(Anima::RUN_L);
					else 
						_animaIter = GetAnima(Anima::INIT_L);
				}	
			}

			// 射擊
			if ((*_nowWeapon)->CanFire() && target != nullptr && d >= MINSEARCH && d <= MAXSEARCH)// 找到敵人朝敵人射擊
			{
				double vx = (double)(target->CenterX() - this->CenterX()) / d;
				double vy = (double)(target->CenterY() - this->CenterY()) / d;
				(*_nowWeapon)->Shoot(vx, vy);
			}
			else if(target != nullptr && _attCounter == 0 && d < MINSEARCH) // 近戰攻擊
			{
				_attCounter = _ATTDELAY;
				target->TakeDmg(_damage);
			}
			else if ((*_nowWeapon)->CanFire()) // 沒找到敵人朝 vector 射擊
			{
				(*_nowWeapon)->Shoot(_vector[0], _vector[1]);
			}
		}
		

		// 近戰攻擊計數
		if (_attCounter > 0)
			_attCounter--;
		// 護頓計數
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
		// 死亡倒數
		if(--_deathCounter == 0)
			this->SetDie(false);
	}

	void CCharacter::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		/*if (other->GetTag() == "enemy")
		{
			other->SetXY(other->GetX1(), other->GetX2());
			other->SetVector(other->GetVectorX() + this->GetVectorX(), other->GetVectorY() + this->GetVectorY());
		}*/
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
		_shieldCounter = GAME_CYCLE_TIME * 5; // 5秒
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

	void  CCharacter::ModifyVector(int index, int plus) //	調整向量範圍 沒用上
	{
		if (index > 1 || index < 0)
			return;
		_vector[index] += plus;
		if (_vector[index] > 1)
			_vector[index] = 1;
		else if (_vector[index] < -1)
			_vector[index] = -1;
	}

	bool  CCharacter::hasObstacle(CGameMap* map, CGameObj* obj1, CGameObj* obj2)
	{
		bool has = false;
		double d = obj1->Distance(obj2);
		int t = (int)(d / MYMAPHIGH);
		int x = obj1->CenterX(), y = obj1->CenterY();
		int vx = (int)((double)(obj2->CenterX() - x) * MYMAPWIDTH / d);
		int vy = (int)((double)(obj2->CenterY() - y) * MYMAPHIGH / d);
		while (t--)
		{
			if (map->IsContent(x, y, CGameMap::ContentType::WALL))
			{
				has = true;
				break;
			}
			x += vx;
			y += vy;
		}
		return has;
	}

	vector<CAnimation>::iterator CCharacter::GetAnima(Anima type)
	{
		return _animas.begin() + (int)type;
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

	void CCharacter::SetXY(int x, int y)
	{
		_mx = x;
		_my = y;
	}
	

}