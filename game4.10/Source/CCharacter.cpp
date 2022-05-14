#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"

namespace game_framework {
	CCharacter* CCharacter::_nowPlayer = nullptr;

	CCharacter::CCharacter():_ATTDELAY(10)
	{
		//	�ʵe���J
		const int AnimaSize = (int)Anima::ANIMACOUNT;
		_animas.clear();
		_animas.reserve(AnimaSize);
		CAnimation animation;
		animation.SetDelayCount(3);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(animation);

		//	�ݩʳ]�w
		_hp = _maxHp = 6;
		_mp = _maxMp = 180;
		_shield = _maxShield = 5;
		_damage = 4;
		_moveSpeed = 10;
		_showPriority = 10;
		_gold = 0;
		this->Reset();
		this->SetTag("player");
		this->SetFree(false);

		//	�Z���]�w
		_weapons[0] = new CGameWeapon(this);
		_weapons[1] = nullptr;
		_nowWeapon = &_weapons[0];
		(*_nowWeapon)->SetTarget("enemy");
		(*_nowWeapon)->SetAttributes(10, 1, 25, 2);

	}

	void CCharacter::Init()
	{
		// GameOver��l��
		_hp = _maxHp;
		_mp = _maxMp;
		_shield = _maxShield;
		_gold = 0;

		// ���m����l�Z��
		free();
		_weapons[0] = new CGameWeapon(this);
		_weapons[1] = nullptr;
		_nowWeapon = &_weapons[0];
		(*_nowWeapon)->LoadBitmap();
		(*_nowWeapon)->SetTarget("enemy");
		(*_nowWeapon)->SetAttributes(10, 1, 25, 2);

	}

	void CCharacter::Reset()
	{
		_doSomeThing = false;
		_canAttack = true;
		_canInteractive = false;
		_attCounter = 0;
		_deathCounter = GAME_ONE_SECONED * 2;
		_shieldCounter = GAME_ONE_SECONED;
		CCharacter::CGameObj::Reset();
		_vector[0] = 1;	//�w�]�¥k
		_DT = 0;

		// �X���ʵe���m
		if(GetAnima(Anima::APPEARANCE)->BmpSize() != 0)
			GetAnima(Anima::APPEARANCE)->Reset();
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

		_animaIter = GetAnima(Anima::APPEARANCE);
		_animaIter->AddBitmap(IDB_playerAppearance_0, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_playerAppearance_1, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_playerAppearance_2, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_playerAppearance_3, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_playerAppearance_4, RGB(0, 0, 0));

		_animaIter = _animas.begin();

		(*_nowWeapon)->LoadBitmap();
	}

	void CCharacter::OnShow(CGameMap* map)
	{
		_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my - 20));
		_animaIter->OnShow();
		if(!_isDie)
			(*_nowWeapon)->OnShow(map);
		if (!GetAnima(Anima::APPEARANCE)->IsFinalBitmap())
		{
			GetAnima(Anima::APPEARANCE)->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my - 20));
			GetAnima(Anima::APPEARANCE)->OnShow();
		}
	}

	void CCharacter::OnMove(CGameMap *map)
	{
		if (!GetAnima(Anima::APPEARANCE)->IsFinalBitmap())
		{
			GetAnima(Anima::APPEARANCE)->OnMove();
			return;
		}
		//	�ʵe����
		_animaIter->OnMove();

		//	�ʵe�P�_
		if (_isMovingRight) 
			_DT = 0;
		else if (_isMovingLeft) 
			_DT = 4;
		
		if (this->IsMoveing())
		{
			if (_DT == 0)
				_animaIter = GetAnima(Anima::RUN_R);
			else
				_animaIter = GetAnima(Anima::RUN_L);
		}
		else if (_DT == 0)
			_animaIter = GetAnima(Anima::INIT_R);
		else
			_animaIter = GetAnima(Anima::INIT_L);
				

		const double MAXSEARCH = 500.0;	// �̤j�j���d�� 
		// ���s�����ĤH
		vector<CGameObj*> enemys = CGameTool::FindObjsBy(CGameObj::_allObj,
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
			double ed = this->Distance(enemy);
			if (d > ed && !hasObstacle(map, this, enemy))
			{
				d = ed;
				target = enemy;
			}
		}

		//	���Ⲿ��
		vector<CGameObj*> roomWalls = CGameTool::FindObjsBy(CGameObj::_allObj,
			[](CGameObj* obj)
			{
				return obj->GetTag() == "roomwall";
			}
		);
		int tempx = _mx, tempy = _my;
		bool j = false;

		for (int i = 0; i < _moveSpeed; i++)
		{
			
			if (_isMovingLeft)
			{
				_mx -= 1;
			}
			else if (_isMovingRight)
			{
				_mx += 1;
			}
			else
			{
				break;
			}

			j = false;
			if (CCharacter::CGameObj::Collision(map))
			{
				j = true;
			}
			else if ((int)roomWalls.size() > 0)
			{
				
				for (CGameObj* obj : roomWalls)
				{
					if (this->Collision(obj))
					{
						j = true;
						break;
					}
				}
			}

			if (j)
			{
				_mx = tempx;
				break;
			}
			else
			{
				tempx = _mx;
			}

		}

		//	�ù����� (�§�쪺�ĤH�A�μ����ê����)
		int screenSpeed = 5;
		if (target == nullptr)
		{
			if (j)
			{
				if (_isMovingLeft)
				{
					map->ModifyDsx(-screenSpeed);
				}
				else if (_isMovingRight)
				{
					map->ModifyDsx(screenSpeed);
				}
			}
			else
			{
				map->ModifyDsx(screenSpeed, 0);
			}
		}

		for (int i = 0; i < _moveSpeed; i++)
		{

			if (_isMovingUp)
			{
				_my -= 1;
			}
			else if (_isMovingDown)
			{
				_my += 1;
			}
			else
			{
				break;
			}

			j = false;
			if (CCharacter::CGameObj::Collision(map))
			{
				j = true;
			}
			else if ((int)roomWalls.size() > 0)
			{

				for (CGameObj* obj : roomWalls)
				{
					if (this->Collision(obj))
					{
						j = true;
						break;
					}
				}
			}
			if (j)
			{
				_my = tempy;
				break;
			}
			else
			{
				tempy = _my;
			}
		}
		
		if (target == nullptr)
		{
			if (j)
			{
				if (_isMovingUp)
				{
					map->ModifyDsy(-screenSpeed);
				}
				else if (_isMovingDown)
				{
					map->ModifyDsy(screenSpeed);
				}
			}
			else
			{
				map->ModifyDsy(screenSpeed, 0);
			}
		}

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

		//	�Z������
		(*_nowWeapon)->SetCenter(this->CenterX(), this->CenterY() - 10);
		(*_nowWeapon)->OnMove(map);
		(*_nowWeapon)->SetDT(_DT);

		// �g�����ܧ󨤦�B�Z���¦V�B�ù�����
		if (target != nullptr)
		{
			//	�ù�(�E�J��ĤH�P���a����)
			int vx = (target->CenterX() - this->CenterX()) >> 1;
			int vy = (target->CenterY() - this->CenterY()) >> 1;
			
			while (vx > SCREEN_MOVE_XLIMIT || vx < -SCREEN_MOVE_XLIMIT || vy > SCREEN_MOVE_YLIMIT || vy < -SCREEN_MOVE_YLIMIT)
			{
				vx >>= 1, vy >>= 1;
			}
			
			map->ModifyDsx(screenSpeed, vx);
			map->ModifyDsy(screenSpeed, vy);
		
			//	�ʵe
			if (target->CenterX() - this->CenterX() > 0)
			{
				(*_nowWeapon)->SetDT(0); 
				if (this->IsMoveing())
					_animaIter = GetAnima(Anima::RUN_R);
				else
					_animaIter = GetAnima(Anima::INIT_R);
			}
			else
			{
				(*_nowWeapon)->SetDT(4);
				if (this->IsMoveing())
					_animaIter = GetAnima(Anima::RUN_L);
				else
					_animaIter = GetAnima(Anima::INIT_L);
			}
		}

		//	���U Q ��
		if (_doSomeThing)
		{
			if (_canInteractive)		// ���󤬰��u��
			{
				_canInteractive = false;
			}
			else if (target != nullptr)	// ���ĤH�¼ĤH�g��
			{
				const double MINSEARCH = 0.0;	// �̤p�j���d�� (�ثe�S��)
				if ((*_nowWeapon)->CanFire() && d <= MAXSEARCH)// ���ĤH�¼ĤH�g��
				{
					double vx = (double)(target->CenterX() - this->CenterX()) / d;
					double vy = (double)(target->CenterY() - this->CenterY()) / d;
					(*_nowWeapon)->Shoot(vx, vy);
					this->ModifyMp(-(*_nowWeapon)->GetCost());
				}
				else if (_attCounter == 0 && d < MINSEARCH) // ��ԧ���
				{
					_attCounter = _ATTDELAY;
					target->TakeDmg(_damage);
				}
			}
			else if ((*_nowWeapon)->CanFire()) // �S���ĤH�� vector �g��
			{
				(*_nowWeapon)->Shoot(_vector[0], _vector[1]);
				this->ModifyMp(-(*_nowWeapon)->GetCost());
			}
		}
		

		// ��ԧ����p��
		if (_attCounter > 0)
			_attCounter--;
		// �@�y�p��
		if (--_shieldCounter == 0)
		{
			_shieldCounter = GAME_ONE_SECONED;
			ModifyShield(1);
		}
			
	}

	void CCharacter::OnDie(CGameMap* map)
	{
		_animaIter = GetAnima(CCharacter::Anima::DIE);
		_animaIter->OnMove();
		// ���`�˼�
		if(--_deathCounter == 0)
			this->SetDie(false);
	}

	void CCharacter::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		if (other->GetTag() == "cleartreasure" && other->IsEnable())	//	�q���_�۪���
		{
			other->TakeDmg(99999);
		}	
		else if (other->GetTag() == "gold")				//	����
		{
			this->ModifyGold(1 + rand() % 2);
		}
		else if (other->GetTag() == "energyball")		//	��q�y(MP)
		{
			this->ModifyMp((1 + rand() % 4) << 1);
		}
		else if (other->GetTag() == "treasure")			//	�@���_�c
		{
			if (_doSomeThing && other->IsEnable())
				other->TakeDmg(99999);
			_canInteractive = true;
		}
		else if (other->GetTag() == "redpotion")		//	���Ĥ�
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->TakeDmg(-2);
				other->TakeDmg(99999);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "bigredpotion")		//	�j���Ĥ�
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->TakeDmg(-4);
				other->TakeDmg(99999);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "bulepotion")		//	���Ĥ�
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->ModifyMp(40);
				other->TakeDmg(99999);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "bigbulepotion")	//	�j���Ĥ�
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->ModifyMp(80);
				other->TakeDmg(99999);
			}
			_canInteractive = true;
		}

		/*if (other->GetTag() == "enemy")
		{
			other->SetXY(other->GetX1(), other->GetX2());
			other->SetVector(other->GetVectorX() + this->GetVectorX(), other->GetVectorY() + this->GetVectorY());
		}*/
	}

	void CCharacter::OnKeyUp(char nChar)
	{
		//	Q �� �ť� �g��
		const char KEY_SPACE = 0x20;
		const char KEY_Q = 0x51;
		const char KEY_W = 0x57;
		const char KEY_S = 0x53;
		const char KEY_A = 0x41;
		const char KEY_D = 0x44;
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y

		if (nChar == KEY_SPACE || nChar == KEY_Q)
		{
			_doSomeThing = false;
		}

		if (nChar == KEY_LEFT || nChar == KEY_A)
			this->SetMovingLeft(false);
		if (nChar == KEY_RIGHT || nChar == KEY_D)
			this->SetMovingRight(false);
		if (nChar == KEY_UP || nChar == KEY_W)
			this->SetMovingUp(false);
		if (nChar == KEY_DOWN || nChar == KEY_S)
			this->SetMovingDown(false);
	}

	void CCharacter::OnKeyDown(char nChar)
	{
		//	Q �� �ť� �g��
		const char KEY_SPACE = 0x20;
		const char KEY_Q = 0x51;
		const char KEY_W = 0x57;
		const char KEY_S = 0x53;
		const char KEY_A = 0x41;
		const char KEY_D = 0x44;
		const char KEY_LEFT = 0x25;		// keyboard���b�Y
		const char KEY_UP = 0x26;		// keyboard�W�b�Y
		const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
		const char KEY_DOWN = 0x28;		// keyboard�U�b�Y

		if (nChar == KEY_SPACE || nChar == KEY_Q)
		{
			_doSomeThing = true;
		}

		if (nChar == KEY_LEFT || nChar == KEY_A)
			this->SetMovingLeft(true);
		if (nChar == KEY_RIGHT || nChar == KEY_D)
			this->SetMovingRight(true);
		if (nChar == KEY_UP || nChar == KEY_W)
			this->SetMovingUp(true);
		if (nChar == KEY_DOWN || nChar == KEY_S)
			this->SetMovingDown(true);
	}

	void CCharacter::TakeDmg(int dmg)
	{
		if (dmg > 0)
		{
			_shieldCounter = GAME_ONE_SECONED * 5; // �� 5 ��
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

	void CCharacter::ModifyVector(int index, int plus) //	�վ�V�q�d�� �S�ΤW
	{
		if (index > 1 || index < 0)
			return;
		_vector[index] += plus;
		if (_vector[index] > 1)
			_vector[index] = 1;
		else if (_vector[index] < -1)
			_vector[index] = -1;
	}

	bool CCharacter::hasObstacle(CGameMap* map, CGameObj* obj1, CGameObj* obj2)
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

	bool CCharacter::IsDoingSomeThing()
	{
		return _doSomeThing;
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

	int CCharacter::GetX2()	//	�I���d��վ�
	{
		return _mx + 49;
	}
	int CCharacter::GetY2() //	�I���d��վ�
	{
		return _my + 30;
	}

	int CCharacter::GetGold()
	{
		return _gold;
	}

	void CCharacter::ModifyGold(int value)
	{
		_gold += value;
	}

	void CCharacter::ModifyMp(int value)
	{
		_mp += value;
		if (_mp < 0)
			_mp = 0;
		else if (_mp > _maxMp)
			_mp = _maxMp;
	}

	void CCharacter::SetXY(int x, int y)
	{
		_mx = x;
		_my = y;
		(*_nowWeapon)->SetCenter(this->CenterX(), this->CenterY() - 10);
	}
	

}