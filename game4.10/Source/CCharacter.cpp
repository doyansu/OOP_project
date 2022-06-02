#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"
#include "CGameFactorys.h"
#include "CUISkill.h"


namespace game_framework {
	CCharacter* CCharacter::_nowPlayer = nullptr;

	CCharacter::CCharacter():_SKILLCD(8 * GAME_ONE_SECONED), _SKILLTD(5 * GAME_ONE_SECONED)
	{
		//	�ʵe���J
		const int AnimaSize = (int)Anima::ANIMACOUNT;
		_animas.clear();
		_animas.reserve(AnimaSize);
		CAnimation animation;
		animation.SetDelayCount(5);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(animation);

		//	�ݩʳ]�w
		_hp = _maxHp = 6;
		_mp = _maxMp = 180;
		_shield = _maxShield = 5;
		_damage = 4;
		_moveSpeed = 8;
		_showPriority = 10;
		_gold = 0;
		_skillWeapon = nullptr;
		_tag = "player";
		_needFree = false;
		_goldInteger.SetColor(CInteger::Color::YELLOW);
		_goldInteger.SetSurviveTime(GAME_ONE_SECONED >> 1);
		_eneryInteger.SetColor(CInteger::Color::BLUE);
		_eneryInteger.SetSurviveTime(GAME_ONE_SECONED >> 1);
		this->Reset();

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
		_weapons[0] = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::Type::INIT);
		_weapons[1] = nullptr;
		_nowWeapon = 0;
		_weapons[_nowWeapon]->SetUser(this);
		_weapons[_nowWeapon]->SetTarget("enemy");

	}

	void CCharacter::Reset()
	{
		_doSomeThing = false;
		_canInteractive = false;
		_skillCounter = _SKILLTD + _SKILLCD;
		_deathCounter = GAME_ONE_SECONED * 2;
		_shieldCounter = GAME_ONE_SECONED;
		CCharacter::CGameObj::Reset();
		_vector[0] = 1;	//�w�]�¥k
		_DT = 1;

		//	���]�Ʀr
		_dmgInteger.Kill();				
		_goldInteger.Kill();
		_eneryInteger.Kill();

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
		{
			delete _weapons[0];
			_weapons[0] = nullptr;
		}
		if (_weapons[1] != nullptr)
		{
			delete _weapons[1];
			_weapons[1] = nullptr;
		}
		if (_skillWeapon != nullptr)
		{
			delete _skillWeapon;
			_skillWeapon = nullptr;
		}
	}

	void CCharacter::LoadBitmap()
	{
		if (_isLoad)
			return;

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


		//	�Z���]�w
		_weapons[0] = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::Type::INIT);
		_weapons[1] = nullptr;
		_nowWeapon = 0;
		_weapons[_nowWeapon]->SetUser(this);
		_weapons[_nowWeapon]->SetTarget("enemy");

		_isLoad = true;
	}

	void CCharacter::OnShow(CGameMap* map)
	{
		if (GetAnima(Anima::APPEARANCE)->IsFinalBitmap())
		{
			if (!_isDie && _weapons[_nowWeapon ^ 1] != nullptr)
				_weapons[_nowWeapon^1]->OnShow(map);
			_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my - 20));
			_animaIter->OnShow();
			if (!_isDie)
			{
				_weapons[_nowWeapon]->OnShow(map);
				if (_skillCounter < _SKILLTD)
					_skillWeapon->OnShow(map);
			}
			// ��ܼƦr
			_dmgInteger.SetTopLeft(map->ScreenX(this->CenterX() - (_dmgInteger.GetWidth() >> 1)), map->ScreenY(this->GetY1() - _dmgInteger.GetHeight() - 20));
			_dmgInteger.OnShow();
			if (!_goldInteger.IsSurvive())
				_goldInteger.SetTopLeft(map->ScreenX(_mx - 5 + rand() % this->GetWidth()), map->ScreenY(_my - 20));
			_goldInteger.OnShow();
			if (!_eneryInteger.IsSurvive())
				_eneryInteger.SetTopLeft(map->ScreenX(_mx - 5 + rand() % this->GetWidth()), map->ScreenY(_my - 20));
			_eneryInteger.OnShow();
		}
		else
		{
			GetAnima(Anima::APPEARANCE)->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my - 50));
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

		if (_isMovingRight)
			_DT = 1;
		else if (_isMovingLeft)
			_DT = 0;

		//	�ʵe�P�_	
		if (this->IsMoveing())
		{
			if (_DT == 1)
				_animaIter = GetAnima(Anima::RUN_R);
			else
				_animaIter = GetAnima(Anima::RUN_L);
		}
		else if (_DT == 1)
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
			if (d > ed && !this->hasObstacle(map, enemy))
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
		int Speed = _moveSpeed;
		int tempx = _mx, tempy = _my;
		bool j = false;

		if ((_isMovingDown || _isMovingUp) && (_isMovingLeft || _isMovingRight))
			Speed = Speed * 10 / 13;

		for (int i = 0; i < Speed; i++)
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

		for (int i = 0; i < Speed; i++)
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
		_weapons[_nowWeapon]->SetCenter(this->CenterX(), this->CenterY() - 10);
		_weapons[_nowWeapon]->OnMove(map);
		if (_weapons[_nowWeapon ^ 1] != nullptr)
		{
			//	�N�ĤG��Z���I�b����
			if (_DT)
			{
				_weapons[_nowWeapon ^ 1]->SetCenter(this->CenterX() - 5, this->CenterY() - 10);
				_weapons[_nowWeapon ^ 1]->SetDT(5);
			}
			else
			{
				_weapons[_nowWeapon ^ 1]->SetCenter(this->CenterX() + 5, this->CenterY() - 10);
				_weapons[_nowWeapon ^ 1]->SetDT(7);
			}
		}
		
		if(_vector[1] <= 0)
			_weapons[_nowWeapon]->SetDT(CGameTool::TwoVectorAngle(_vector[0], _vector[1], 1.0, 0.0) / 45);
		else
			_weapons[_nowWeapon]->SetDT(8 - CGameTool::TwoVectorAngle(_vector[0], _vector[1], 1.0, 0.0) / 45);

		//	�ޯॿ�b�ϥ�
		if (_skillCounter < _SKILLTD)
		{
			_skillWeapon->OnMove(map);
			if (_DT)
				_skillWeapon->SetCenter(this->CenterX() + 10, this->CenterY() - 15);
			else
				_skillWeapon->SetCenter(this->CenterX() - 10, this->CenterY() - 15);
			if (_vector[1] <= 0)
				_skillWeapon->SetDT(CGameTool::TwoVectorAngle(_vector[0], _vector[1], 1.0, 0.0) / 45);
			else
				_skillWeapon->SetDT(8 - CGameTool::TwoVectorAngle(_vector[0], _vector[1], 1.0, 0.0) / 45);
		}

		// ���ĤH���ܧ󨤦�B�Z���¦V�B�ù�����
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
		
			//	����ʵe
			if (target->CenterX() - this->CenterX() > 0)
			{
				if (this->IsMoveing())
					_animaIter = GetAnima(Anima::RUN_R);
				else
					_animaIter = GetAnima(Anima::INIT_R);
			}
			else
			{
				if (this->IsMoveing())
					_animaIter = GetAnima(Anima::RUN_L);
				else
					_animaIter = GetAnima(Anima::INIT_L);
			}

			//	�Z���ʵe
			int tx = target->CenterX() - this->CenterX();
			int ty = target->CenterY() - this->CenterY();
			if (ty <= 0)
				_weapons[_nowWeapon]->SetDT(CGameTool::TwoVectorAngle(tx, ty, 1.0, 0.0) / 45);
			else
				_weapons[_nowWeapon]->SetDT(8 - CGameTool::TwoVectorAngle(tx, ty, 1.0, 0.0) / 45);

			//	���b�ϥΧޯ�
			if (_skillCounter < _SKILLTD)
			{
				if (ty <= 0)
					_skillWeapon->SetDT(CGameTool::TwoVectorAngle(tx, ty, 1.0, 0.0) / 45);
				else
					_skillWeapon->SetDT(8 - CGameTool::TwoVectorAngle(tx, ty, 1.0, 0.0) / 45);
			}
		}


		//	���U Z ��
		if (_doSomeThing)
		{
			if (_canInteractive)		// ���󤬰��u��
			{
				_canInteractive = false;
			}
			else if (target != nullptr)	// ���ĤH�¼ĤH�g��
			{
				const double MINSEARCH = 50;	// �̤p�j���d�� (�ثe�S��)
				if (_weapons[_nowWeapon]->CanFire() && d >= MINSEARCH)// ���ĤH�¼ĤH�g��
				{
					double vx = (double)(target->CenterX() - this->CenterX()) / d;
					double vy = (double)(target->CenterY() - this->CenterY()) / d;
					if (_mp >= _weapons[_nowWeapon]->GetCost())
					{
						_weapons[_nowWeapon]->Shoot(vx, vy);
						this->ModifyMp(-_weapons[_nowWeapon]->GetCost());
					}
				}
				else if (d < MINSEARCH) // ��ԧ���
				{
					//target->TakeDmg(_damage);
					CGameBullet* handKnife = ProductFactory<CGameBullet>::Instance().GetProduct((int)CGameBullet::Type::HandKnife);
					handKnife->SetXY((this->CenterX() + target->CenterX() - handKnife->GetWidth()) / 2, (this->CenterY() + target->CenterY() - handKnife->GetHeight()) / 2);
					CGameObj::AddObj(handKnife);
					_doSomeThing = false;
				}

				//	���b�ϥΧޯ�
				if (_skillCounter < _SKILLTD && _skillWeapon->CanFire() && d >= MINSEARCH)
				{
					double vx = (double)(target->CenterX() - this->CenterX()) / d;
					double vy = (double)(target->CenterY() - this->CenterY()) / d;
					if (_mp >= _skillWeapon->GetCost())
					{
						_skillWeapon->Shoot(vx, vy);
						this->ModifyMp(-_skillWeapon->GetCost());
					}
					
				}
			}
			else if (_mp >= _weapons[_nowWeapon]->GetCost())// �S���ĤH�� vector �g��
			{
				if (_weapons[_nowWeapon]->CanFire())
				{
					_weapons[_nowWeapon]->Shoot(_vector[0], _vector[1]);
					this->ModifyMp(-_weapons[_nowWeapon]->GetCost());
				}
				//	���b�ϥΧޯ�
				if (_skillCounter < _SKILLTD && _skillWeapon->CanFire())
				{
					_skillWeapon->Shoot(_vector[0], _vector[1]);
					this->ModifyMp(-_skillWeapon->GetCost());
				}
			}
		}
		
		// �@�y�p��
		if (--_shieldCounter == 0)
		{
			_shieldCounter = GAME_ONE_SECONED;
			ModifyShield(1);
		}
		if (_skillCounter <= _SKILLTD + _SKILLCD)
		{
			if(_skillCounter < _SKILLTD)
				CUISkill::Instance().SetValue(100 * (_SKILLTD - _skillCounter) / _SKILLTD);
			else 
				CUISkill::Instance().SetValue(100 * (_skillCounter - _SKILLTD) / _SKILLCD);
			_skillCounter++;
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
			//	���񭵮�
			CAudio::Instance()->Play(AUDIO_ID::AUDIO_GET_COIN);
		}
		else if (other->GetTag() == "energyball")		//	��q�y(MP)
		{
			this->ModifyMp((1 + rand() % 4) << 1);
			//	���񭵮�
			CAudio::Instance()->Play(AUDIO_ID::AUDIO_GET_ENERGY);
		}
		else if (other->GetTag() == "treasure")			//	�@���_�c
		{
			if (other->IsEnable())
			{
				_canInteractive = true;
				if (_doSomeThing)
					other->TakeDmg(99999);
			}
		}
		else if (other->GetTag() == "redpotion")		//	���Ĥ�
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->TakeDmg(-2);
				other->TakeDmg(99999);
				CAudio::Instance()->Play(AUDIO_ID::AUDIO_HEALTH);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "bigredpotion")		//	�j���Ĥ�
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->TakeDmg(-4);
				other->TakeDmg(99999);
				CAudio::Instance()->Play(AUDIO_ID::AUDIO_HEALTH);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "bulepotion")		//	���Ĥ�
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->ModifyMp(40);
				other->TakeDmg(99999);
				CAudio::Instance()->Play(AUDIO_ID::AUDIO_HEALTH);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "bigbulepotion")	//	�j���Ĥ�
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->ModifyMp(80);
				other->TakeDmg(99999);
				CAudio::Instance()->Play(AUDIO_ID::AUDIO_HEALTH);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "weapon")			//	�Z��
		{
			if (_doSomeThing)
			{
				CAudio::Instance()->Play(AUDIO_SWITCH_WEAPON);
				if (_weapons[_nowWeapon ^ 1] == nullptr)	// �u���@��Z��
				{
					_weapons[_nowWeapon ^ 1] = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::WeaponMap[other]->GetType());
					//_weapons[_nowWeapon ^ 1] = CGameWeapon::WeaponMap[other];
					_weapons[_nowWeapon ^ 1]->SetUser(this);
					_weapons[_nowWeapon ^ 1]->SetTarget("enemy");
					other->SetEnable(false);
				}
				else  // ������e�Z��
				{
					_weapons[_nowWeapon]->SetUser(nullptr);
					CGameObj::AddObj(_weapons[_nowWeapon]);
					_weapons[_nowWeapon] = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::WeaponMap[other]->GetType());
					_weapons[_nowWeapon]->SetUser(this);
					_weapons[_nowWeapon]->SetTarget("enemy");
					other->SetEnable(false);
				}
				_doSomeThing = false;
			}
			_canInteractive = true;
		}
		else
		{
		}

		/*if (other->GetTag() == "enemy")
		{
			other->SetXY(other->GetX1(), other->GetX2());
			other->SetVector(other->GetVectorX() + this->GetVectorX(), other->GetVectorY() + this->GetVectorY());
		}*/
	}

	void CCharacter::OnKeyUp(char nChar)
	{
		//	Z�� �ť� �g��
		const char KEY_SPACE = 0x20;
		const char KEY_Q = 0x51;
		const char KEY_W = 0x57;
		const char KEY_S = 0x53;
		const char KEY_A = 0x41;
		const char KEY_D = 0x44;
		const char KEY_Z = 0x5A;
		const char KEY_X = 0x58;
		const char KEY_C = 0x43;
		const char KEY_E = 0x45;
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y

		switch (nChar)
		{
		case KEY_SPACE:
		case KEY_Z:
			_doSomeThing = false;
			break;
		case KEY_LEFT:
		case KEY_A:
			this->SetMovingLeft(false);
			break;
		case KEY_RIGHT:
		case KEY_D:
			this->SetMovingRight(false);
			break;
		case KEY_UP:
		case KEY_W:
			this->SetMovingUp(false);
			break;
		case KEY_DOWN:
		case KEY_S:
			this->SetMovingDown(false);
			break;
		default:
			break;
		}
	}

	void CCharacter::OnKeyDown(char nChar)
	{
		//	Z �� �ť� �g��
		const char KEY_SPACE = 0x20;
		const char KEY_Q = 0x51;
		const char KEY_W = 0x57;
		const char KEY_S = 0x53;
		const char KEY_A = 0x41;
		const char KEY_D = 0x44;
		const char KEY_Z = 0x5A;
		const char KEY_X = 0x58;
		const char KEY_C = 0x43;
		const char KEY_E = 0x45;
		const char KEY_LEFT = 0x25;		// keyboard���b�Y
		const char KEY_UP = 0x26;		// keyboard�W�b�Y
		const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
		const char KEY_DOWN = 0x28;		// keyboard�U�b�Y

		switch (nChar)
		{
		case KEY_SPACE:
		case KEY_Z:
			_doSomeThing = true;
			break;
		case KEY_LEFT:
		case KEY_A:
			this->SetMovingLeft(true);
			break;
		case KEY_RIGHT:
		case KEY_D:
			this->SetMovingRight(true);
			break;
		case KEY_UP:
		case KEY_W:
			this->SetMovingUp(true);
			break;
		case KEY_DOWN:
		case KEY_S:
			this->SetMovingDown(true);
			break;
		case KEY_Q:
		case KEY_X:
			SwitchWeapon();
			break;
		case KEY_E:
		case KEY_C:
			UseSkill();
			break;
		default:
			break;
		}
	}

	void CCharacter::TakeDmg(int dmg)
	{
		_dmgInteger.AddDmg(-dmg);
		if (dmg > 0)
		{
			_shieldCounter = GAME_ONE_SECONED * 5; // �� 5 ��
			if (_shield)
			{
				_shield -= dmg;
				if (_shield <= 0)
				{
					CAudio::Instance()->Play(AUDIO_SHIELDBREAK);
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

	void CCharacter::UseSkill()
	{
		if (_skillCounter >= _SKILLTD + _SKILLCD)
		{
			_skillCounter = 0;
			if (_skillWeapon != nullptr)
				delete _skillWeapon;
			_skillWeapon = ProductFactory<CGameWeapon>::Instance().GetProduct((int)_weapons[_nowWeapon]->GetType());
			_skillWeapon->SetUser(this);
			_skillWeapon->SetTarget("enemy");
		}
	}

	void CCharacter::SwitchWeapon()
	{
		if (_weapons[_nowWeapon ^ 1] != nullptr)
		{
			//	�����Z��
			_nowWeapon ^= 1;
			//	���񭵮�
			CAudio::Instance()->Play(AUDIO_SWITCH_WEAPON);
			// �����Z���|�����ޯ�
			if (_skillCounter < _SKILLTD)
			{
				_skillCounter = _SKILLTD;
			}
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

	CGameWeapon* CCharacter::GetNowWeapon()
	{
		return _weapons[_nowWeapon];
	}

	void CCharacter::ModifyGold(int value)
	{
		_goldInteger.AddDmg(value);
		_gold += value;
	}

	void CCharacter::ModifyMp(int value)
	{
		if(value > 0)
			_eneryInteger.AddDmg(value);
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
		_weapons[_nowWeapon]->SetCenter(this->CenterX(), this->CenterY() - 10);
	}
	

}