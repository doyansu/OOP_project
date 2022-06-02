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
		//	動畫載入
		const int AnimaSize = (int)Anima::ANIMACOUNT;
		_animas.clear();
		_animas.reserve(AnimaSize);
		CAnimation animation;
		animation.SetDelayCount(5);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(animation);

		//	屬性設定
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
		// GameOver初始化
		_hp = _maxHp;
		_mp = _maxMp;
		_shield = _maxShield;
		_gold = 0;

		// 重置為初始武器
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
		_vector[0] = 1;	//預設朝右
		_DT = 1;

		//	重設數字
		_dmgInteger.Kill();				
		_goldInteger.Kill();
		_eneryInteger.Kill();

		// 出場動畫重置
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


		//	武器設定
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
			// 顯示數字
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
		//	動畫移動
		_animaIter->OnMove();

		if (_isMovingRight)
			_DT = 1;
		else if (_isMovingLeft)
			_DT = 0;

		//	動畫判斷	
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
				

		const double MAXSEARCH = 500.0;	// 最大搜索範圍 
		// 找到存活的敵人
		vector<CGameObj*> enemys = CGameTool::FindObjsBy(CGameObj::_allObj,
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
			if (d > ed && !this->hasObstacle(map, enemy))
			{
				d = ed;
				target = enemy;
			}
		}

		//	角色移動
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

		//	螢幕移動 (朝找到的敵人，或撞到障礙移動)
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

		//	武器移動
		_weapons[_nowWeapon]->SetCenter(this->CenterX(), this->CenterY() - 10);
		_weapons[_nowWeapon]->OnMove(map);
		if (_weapons[_nowWeapon ^ 1] != nullptr)
		{
			//	將第二把武器背在身後
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

		//	技能正在使用
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

		// 找到敵人時變更角色、武器朝向、螢幕移動
		if (target != nullptr)
		{
			//	螢幕(聚焦到敵人與玩家中間)
			int vx = (target->CenterX() - this->CenterX()) >> 1;
			int vy = (target->CenterY() - this->CenterY()) >> 1;
			
			while (vx > SCREEN_MOVE_XLIMIT || vx < -SCREEN_MOVE_XLIMIT || vy > SCREEN_MOVE_YLIMIT || vy < -SCREEN_MOVE_YLIMIT)
			{
				vx >>= 1, vy >>= 1;
			}
			
			map->ModifyDsx(screenSpeed, vx);
			map->ModifyDsy(screenSpeed, vy);
		
			//	角色動畫
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

			//	武器動畫
			int tx = target->CenterX() - this->CenterX();
			int ty = target->CenterY() - this->CenterY();
			if (ty <= 0)
				_weapons[_nowWeapon]->SetDT(CGameTool::TwoVectorAngle(tx, ty, 1.0, 0.0) / 45);
			else
				_weapons[_nowWeapon]->SetDT(8 - CGameTool::TwoVectorAngle(tx, ty, 1.0, 0.0) / 45);

			//	正在使用技能
			if (_skillCounter < _SKILLTD)
			{
				if (ty <= 0)
					_skillWeapon->SetDT(CGameTool::TwoVectorAngle(tx, ty, 1.0, 0.0) / 45);
				else
					_skillWeapon->SetDT(8 - CGameTool::TwoVectorAngle(tx, ty, 1.0, 0.0) / 45);
			}
		}


		//	按下 Z 鍵
		if (_doSomeThing)
		{
			if (_canInteractive)		// 物件互動優先
			{
				_canInteractive = false;
			}
			else if (target != nullptr)	// 找到敵人朝敵人射擊
			{
				const double MINSEARCH = 50;	// 最小搜索範圍 (目前沒有)
				if (_weapons[_nowWeapon]->CanFire() && d >= MINSEARCH)// 找到敵人朝敵人射擊
				{
					double vx = (double)(target->CenterX() - this->CenterX()) / d;
					double vy = (double)(target->CenterY() - this->CenterY()) / d;
					if (_mp >= _weapons[_nowWeapon]->GetCost())
					{
						_weapons[_nowWeapon]->Shoot(vx, vy);
						this->ModifyMp(-_weapons[_nowWeapon]->GetCost());
					}
				}
				else if (d < MINSEARCH) // 近戰攻擊
				{
					//target->TakeDmg(_damage);
					CGameBullet* handKnife = ProductFactory<CGameBullet>::Instance().GetProduct((int)CGameBullet::Type::HandKnife);
					handKnife->SetXY((this->CenterX() + target->CenterX() - handKnife->GetWidth()) / 2, (this->CenterY() + target->CenterY() - handKnife->GetHeight()) / 2);
					CGameObj::AddObj(handKnife);
					_doSomeThing = false;
				}

				//	正在使用技能
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
			else if (_mp >= _weapons[_nowWeapon]->GetCost())// 沒找到敵人朝 vector 射擊
			{
				if (_weapons[_nowWeapon]->CanFire())
				{
					_weapons[_nowWeapon]->Shoot(_vector[0], _vector[1]);
					this->ModifyMp(-_weapons[_nowWeapon]->GetCost());
				}
				//	正在使用技能
				if (_skillCounter < _SKILLTD && _skillWeapon->CanFire())
				{
					_skillWeapon->Shoot(_vector[0], _vector[1]);
					this->ModifyMp(-_skillWeapon->GetCost());
				}
			}
		}
		
		// 護頓計數
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
		// 死亡倒數
		if(--_deathCounter == 0)
			this->SetDie(false);
	}

	void CCharacter::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		if (other->GetTag() == "cleartreasure" && other->IsEnable())	//	通關寶相物件
		{
			other->TakeDmg(99999);
		}	
		else if (other->GetTag() == "gold")				//	金幣
		{
			this->ModifyGold(1 + rand() % 2);
			//	播放音效
			CAudio::Instance()->Play(AUDIO_ID::AUDIO_GET_COIN);
		}
		else if (other->GetTag() == "energyball")		//	能量球(MP)
		{
			this->ModifyMp((1 + rand() % 4) << 1);
			//	播放音效
			CAudio::Instance()->Play(AUDIO_ID::AUDIO_GET_ENERGY);
		}
		else if (other->GetTag() == "treasure")			//	一般寶箱
		{
			if (other->IsEnable())
			{
				_canInteractive = true;
				if (_doSomeThing)
					other->TakeDmg(99999);
			}
		}
		else if (other->GetTag() == "redpotion")		//	紅藥水
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->TakeDmg(-2);
				other->TakeDmg(99999);
				CAudio::Instance()->Play(AUDIO_ID::AUDIO_HEALTH);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "bigredpotion")		//	大紅藥水
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->TakeDmg(-4);
				other->TakeDmg(99999);
				CAudio::Instance()->Play(AUDIO_ID::AUDIO_HEALTH);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "bulepotion")		//	藍藥水
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->ModifyMp(40);
				other->TakeDmg(99999);
				CAudio::Instance()->Play(AUDIO_ID::AUDIO_HEALTH);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "bigbulepotion")	//	大藍藥水
		{
			if (_doSomeThing && other->IsEnable())
			{
				this->ModifyMp(80);
				other->TakeDmg(99999);
				CAudio::Instance()->Play(AUDIO_ID::AUDIO_HEALTH);
			}
			_canInteractive = true;
		}
		else if (other->GetTag() == "weapon")			//	武器
		{
			if (_doSomeThing)
			{
				CAudio::Instance()->Play(AUDIO_SWITCH_WEAPON);
				if (_weapons[_nowWeapon ^ 1] == nullptr)	// 只有一把武器
				{
					_weapons[_nowWeapon ^ 1] = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::WeaponMap[other]->GetType());
					//_weapons[_nowWeapon ^ 1] = CGameWeapon::WeaponMap[other];
					_weapons[_nowWeapon ^ 1]->SetUser(this);
					_weapons[_nowWeapon ^ 1]->SetTarget("enemy");
					other->SetEnable(false);
				}
				else  // 替換當前武器
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
		//	Z或 空白 射擊
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
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭

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
		//	Z 或 空白 射擊
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
		const char KEY_LEFT = 0x25;		// keyboard左箭頭
		const char KEY_UP = 0x26;		// keyboard上箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		const char KEY_DOWN = 0x28;		// keyboard下箭頭

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
			_shieldCounter = GAME_ONE_SECONED * 5; // 約 5 秒
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
			//	切換武器
			_nowWeapon ^= 1;
			//	播放音效
			CAudio::Instance()->Play(AUDIO_SWITCH_WEAPON);
			// 切換武器會取消技能
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

	void CCharacter::ModifyVector(int index, int plus) //	調整向量範圍 沒用上
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

	int CCharacter::GetX2()	//	碰撞範圍調整
	{
		return _mx + 49;
	}

	int CCharacter::GetY2() //	碰撞範圍調整
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