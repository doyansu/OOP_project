#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEnemy.h"
#include "CCharacter.h"
#include "CGameFactorys.h"
#include "CGameTrackObj.h"

namespace game_framework {
	int CEnemy::_amountDie = 0;

	CEnemy::CEnemy()
	{
		// �ʵe���J
		const int AnimaSize = (int)Anima::ANIMACOUNT;
		_animas.clear();
		_animas.reserve(AnimaSize);
		CAnimation animation;
		animation.SetDelayCount(5);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(animation);

		// �ݩʳ]�w
		this->SetXY(400, 400);
		this->SetShowPriority(1);
		this->_maxHp = this->_hp = 10;
		this->_moveSpeed = 3;
		this->_maxSearch = 300;
		CEnemy::CGameObj::SetTag("enemy");
		_enemyType = Type::INIT;
		_weapon = nullptr;
	}

	CEnemy::~CEnemy()
	{
		free();
	}

	CEnemy::CEnemy(const CEnemy& other):CGameObj(other)
	{
		copy(other);
	}

	/*CEnemy& CEnemy::operator=(const CEnemy& other)
	{
		if (this != &other)
		{
			free();
			copy(other);
		}
		return *this;
	}*/

	void CEnemy::copy(const CEnemy& other)
	{
		this->_enemyType = other._enemyType;
		this->_dmgInteger = other._dmgInteger;
		this->_maxSearch = other._maxSearch;
		if (other._weapon != nullptr)
		{
			_weapon = ProductFactory<CGameWeapon>::Instance().GetProduct((int)other._weapon->GetType());
			_weapon->SetUser(this);
			_weapon->SetTarget("player");
		}
		else
			_weapon = nullptr;
	}

	void CEnemy::free()
	{
		delete _weapon;
		_weapon = nullptr;
	}

	void CEnemy::LoadBitmap()
	{
		_animaIter = GetAnima(CEnemy::Anima::RUN_R);
		_animaIter->AddBitmap(IDB_enemy0_0, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_3, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_enemy0_4, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::RUN_L);
		_animaIter->AddBitmap(IDB_ENEMY0_0_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY0_1_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY0_2_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY0_3_L, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_ENEMY0_4_L, RGB(255, 255, 255));

		_animaIter = GetAnima(CEnemy::Anima::DIE);
		_animaIter->AddBitmap(IDB_enemy0_die, RGB(255, 255, 255));

		*GetAnima(Anima::APPEARANCE) = CAnimationEnemyAppear::Instance();


		_animaIter = _animas.begin();


		// �Z���]�w
		_weapon = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::Type::enemy_0);
		_weapon->SetUser(this);
		_weapon->SetTarget("player");
	}

	void CEnemy::OnShow(CGameMap* map)
	{
		if (GetAnima(Anima::APPEARANCE)->IsFinalBitmap())
		{
			_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my - _animaIter->Height() / 2));
			_animaIter->OnShow();
			if(!_isDie && _weapon != nullptr)
				_weapon->OnShow(map);
			_dmgInteger.SetTopLeft(map->ScreenX(this->CenterX() - (_dmgInteger.GetWidth() >> 1)), map->ScreenY(this->GetY1() - _dmgInteger.GetHeight() - _animaIter->Height() / 2));
			_dmgInteger.OnShow();
		}
		else
		{
			GetAnima(Anima::APPEARANCE)->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my - 50 - _animaIter->Height() / 2));
			GetAnima(Anima::APPEARANCE)->OnShow();
		}
		
	}

	void CEnemy::OnMove(CGameMap *map)
	{
		if (!GetAnima(Anima::APPEARANCE)->IsFinalBitmap())
		{
			GetAnima(Anima::APPEARANCE)->OnMove();
			return;
		}

		// �ĤH����
		_animaIter->OnMove();
		int Speed = _moveSpeed;
		const int randomRange = 20;	// �H���ܤ�V

		if ((rand() % randomRange) == 0)
		{
			_vector[0] = (double)(-100 + rand() % 201) / 100.0;
			_vector[1] = (double)(-100 + rand() % 201) / 100.0;
		}
		
		int dx = (int)((double)Speed * _vector[0]), dy = (int)((double)Speed * _vector[1]);

		_mx += dx;

		if (CGameObj::Collision(map) || CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL))
		{
			_mx -= dx;
		}

		_my += dy;

		if (CGameObj::Collision(map) || CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL))
		{
			_my -= dy;
		}

		// �Z������
		if (_weapon != nullptr)
		{
			_weapon->SetCenter(this->CenterX(), this->CenterY() - _animaIter->Height() / 4);
			_weapon->OnMove(map);
		}
		
		
		CGameObj* player = CCharacter::Instance();
		double d = _maxSearch;
		double vx = 0;
		double vy = 0;
		
		// ��쪱�a
		if (player && !player->hasObstacle(map, this))
		{
			d = this->Distance(player);
			vx = (double)(player->CenterX() - this->CenterX()) / d;
			vy = (double)(player->CenterY() - this->CenterY()) / d;
			// �����ʵe
			if (vx > 0)
				_animaIter = GetAnima(CEnemy::Anima::RUN_R);
			else
				_animaIter = GetAnima(CEnemy::Anima::RUN_L);

			if (_weapon != nullptr)
			{
				if (vy <= 0)
					_weapon->SetDT(CGameTool::TwoVectorAngle(vx * d, vy * d, 1.0, 0.0) / 45);
				else
					_weapon->SetDT(8 - CGameTool::TwoVectorAngle(vx * d, vy * d, 1.0, 0.0) / 45);

				// �Z���g��
				if (_weapon->CanFire() && d < _maxSearch && (rand() % 20 == 0))
				{
					_weapon->Shoot(vx, vy);
				}
			}
		}
		
	}

	void CEnemy::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		/*if (other->GetTag() == "player")
		{
			double vx = _vector[0], vy = _vector[1];
			_vector[0] += other->GetVectorX();
			_vector[1] += other->GetVectorY();
			if (abs(_vector[0]) > 5)
				_vector[0] = vx;
			if (abs(_vector[1]) > 5)
				_vector[1] = vy;
		}*/
	}

	void CEnemy::Die()
	{
		_amountDie++;	// �ĤH���`�ƥ[�@
		this->SetEnable(false);
		this->SetDie(true);
		this->SetCollision(false);
		this->SetShowPriority(0);
		_animaIter = GetAnima(CEnemy::Anima::DIE);
		// �H�� DEAD ����  CAudio::Instance()->Play(AUDIO_DEAD_ENEMY_0 + rand() % (AUDIO_DEAD_ENEMY_COUNT - AUDIO_DEAD_ENEMY_0));
		CAudio::Instance()->Play(AUDIO_DEAD_ENEMY_0);

		if (rand() % 10 < 2)	//	20 % ���������ί�q�y
		{
			int t = 1 + rand() % 3;
			CGameObj* player = CCharacter::Instance();
			while (t--)
			{
				int r = rand() % 2;
				CGameTrackObj* obj = CGameTrackObj::CreateObj(r);
				obj->SetXY(this->CenterX(), this->CenterY());
				obj->SetTarget(player);
				CGameObj::AddObj(obj);
			}
		}
	}

	void CEnemy::OnDie(CGameMap* map)
	{
		if (!GetAnima(Anima::APPEARANCE)->IsFinalBitmap())
		{
			GetAnima(Anima::APPEARANCE)->OnMove();
		}
		_animaIter->OnMove();
	}


	void CEnemy::TakeDmg(int dmg)
	{
		_dmgInteger.AddDmg(-dmg);
		CGameObj::TakeDmg(dmg);
		// �H�� HIT ���� CAudio::Instance()->Play(AUDIO_HIT_ENEMY_0 + rand() % (AUDIO_HIT_ENEMY_COUNT - AUDIO_HIT_ENEMY_0));
		CAudio::Instance()->Play(AUDIO_HIT_ENEMY_0);
	}

	bool CEnemy::hasAppeared()
	{
		return GetAnima(Anima::APPEARANCE)->IsFinalBitmap();
	}

	CEnemy::Type CEnemy::GetType()
	{
		return _enemyType;
	}

	vector<CAnimation>::iterator CEnemy::GetAnima(Anima type)
	{
		return _animas.begin() + (int)type;
	}

	int CEnemy::GetX2()
	{
		return _mx + _animaIter->Width();
	}

	int CEnemy::GetY2()	//	�I���վ�
	{
		return _my + _animaIter->Height() / 2;
	}

}