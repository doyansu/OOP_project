#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameWeapon.h"
#include "CUIWeapon.h"
#include "CGameFactorys.h"


namespace game_framework
{
	map<CGameObj*, CGameWeapon*> CGameWeapon::WeaponMap;

	CGameWeapon::CGameWeapon(CGameObj* user, Type type)
	{
		// 動畫載入
		const int AnimaSize = (int)Anima::ANIMACOUNT;
		_animas.clear();
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation());

		// 屬性設定
		_user = user;
		_fire = false;
		_cost = 0;
		_shootDelay = 10;
		_fireCounter = _shootDelay;
		_bulletSpeed = 20;
		_crit = 0;
		_spread = 0;
		_atk = 0;
		_DT = 1;
		CGameWeapon::CGameObj::SetTag("weapon");
		_center[0] = _center[1] = 0;
		_shootID = AUDIO_ID::AUDIO_GUN_0;
		_collPlayer = false;
		_weaponType = type;

		WeaponMap[(CGameObj*)this] = this;
	}

	CGameWeapon::~CGameWeapon()
	{
		free();
		WeaponMap.erase((CGameObj*)this);
	}

	CGameWeapon::CGameWeapon(const CGameWeapon& other):CGameObj(other)
	{
		copy(other);
	}

	/*CGameWeapon& CGameWeapon::operator=(const CGameWeapon& other)
	{
		
		if (this != &other)
		{
			free();
			//this->CGameObj(other);
			copy(other);
		}
		return *this;
	}*/

	void CGameWeapon::copy(const CGameWeapon& other)
	{
		this->_fire = other._fire;
		this->_cost = other._cost;
		this->_bulletSpeed = other._bulletSpeed;
		this->_shootDelay = other._shootDelay;
		this->_fireCounter = other._fireCounter;
		this->_DT = other._DT;
		this->_user = other._user;
		this->_center[0] = other._center[0];
		this->_center[1] = other._center[1];
		this->_shootID = other._shootID;
		this->_collPlayer = other._collPlayer;
		this->_weaponType = other._weaponType;
		this->_crit = other._crit;
		this->_spread = other._spread;
		this->_atk = other._atk;
		WeaponMap[(CGameObj*)this] = this;
	}

	void CGameWeapon::free()
	{

	}

	void CGameWeapon::LoadBitmap()
	{
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_0);
		_animaIter->AddBitmap(IDB_weapon_0_0, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_45);
		_animaIter->AddBitmap(IDB_weapon_0_45, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_90);
		_animaIter->AddBitmap(IDB_weapon_0_90, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_135);
		_animaIter->AddBitmap(IDB_weapon_0_135, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_180);
		_animaIter->AddBitmap(IDB_weapon_0_180, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_225);
		_animaIter->AddBitmap(IDB_weapon_0_225, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_270);
		_animaIter->AddBitmap(IDB_weapon_0_270, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_315);
		_animaIter->AddBitmap(IDB_weapon_0_315, RGB(255, 255, 255));


		*GetAnima(Anima::ARROW) = CGameArrow::Instance();
		_isLoad = true;
	}

	void CGameWeapon::OnMove(CGameMap* map)
	{
		CGameWeapon::CGameObj::_animaIter->OnMove();

		if (_user == nullptr)	// 無使用者
		{
			_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Theta_0);
			if (_collPlayer)
			{
				GetAnima(Anima::ARROW)->OnMove();
				_collPlayer = false;

				// 武器 UI 調動
				CUIWeapon::Instance().SetMove(false);
				CUIWeapon::Instance().SetValue(_atk, _cost, _crit, _spread);
			}
			else // 重製動畫
			{
				GetAnima(Anima::ARROW)->Reset();
			}
		}
		else
		{
			this->SetXY(this->_center[0] - (this->GetWidth() >> 1), this->_center[1] - (this->GetHeight() >> 2));

			//	射擊間隔計數
			if (!_fire && --_fireCounter == 0)
				_fire = true;
		
			// debug
			/*if (_mx < 0 || _my < 0 || _mx > MYMAPSIZE * MYMAPSIZE || _my > MYMAPSIZE * MYMAPSIZE)
				GAME_ASSERT(false, "武器超出地圖!");*/
		}

		
	}

	void CGameWeapon::OnShow(CGameMap* map)
	{
		_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));	
		_animaIter->OnShow();
		if (_collPlayer && _user == nullptr)
		{
			vector<CAnimation>::iterator iterator = GetAnima(Anima::ARROW);
			iterator->SetTopLeft(map->ScreenX(_mx + ((_animaIter->Width() - iterator->Width()) >> 1)),
				map->ScreenY(_my - iterator->Height()));
			iterator->OnShow();
		}
	}

	void CGameWeapon::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		if (!_collPlayer && other->GetTag() == "player")
		{
			_collPlayer = true;
		}
	}

	void CGameWeapon::Shoot(double x, double y)
	{
		if (_fire)
		{
			// 音效播放
			CAudio::Instance()->Play(_shootID);

			CGameBullet* newbullet = ProductFactory<CGameBullet>::Instance().GetProduct((int)CGameBullet::Type::INIT);
			newbullet->SetSpeed(_bulletSpeed);
			newbullet->SetTarget(_target);
			// 出發點
			newbullet->SetXY(this->CenterX(), this->CenterY());
			// 是否爆擊調整傷害
			newbullet->SetDamage(this->_atk * ((rand() % 50 < 5 + this->_crit) ? 2 : 1));
			// 決定方向
			newbullet->SetVector(x + 0.05 * (-(this->_spread >> 1) + rand() % this->_spread)
				, y + 0.05 * (-(this->_spread >> 1) + rand() % this->_spread));		
			CGameObj::AddObj(newbullet);
			_fire = false;
			_fireCounter = _shootDelay;
		}
	}

	bool CGameWeapon::CanFire() 
	{
		return _fire;
	}

	vector<CAnimation>::iterator CGameWeapon::GetAnima(Anima type)
	{
		return _animas.begin() + (int)type;
	}

	void CGameWeapon::SetDT(int DT)
	{
		_DT = DT;

		switch (_DT)
		{
		case 0:
			_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Theta_0);
			break;
		case 1:
			_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Theta_45);
			break;
		case 2:
			_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Theta_90);
			break;
		case 3:
			_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Theta_135);
			break;
		case 4:
			_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Theta_180);
			break;
		case 5:
			_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Theta_225);
			break;
		case 6:
			_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Theta_270);
			break;
		case 7:
			_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Theta_315);
			break;
		default:
			_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Theta_0);
			break;
		}
	}

	void CGameWeapon::SetTarget(string target)
	{
		_target = target;
	}

	void CGameWeapon::SetUser(CGameObj* user)
	{
		_user = user;
	}

	void CGameWeapon::SetAttributes(int atk, int cost, int bulletSpeed, int shootDelay)
	{
		_atk = atk;
		_cost = cost;
		_bulletSpeed = bulletSpeed;
		_shootDelay = shootDelay;
	}

	void CGameWeapon::SetCenter(int x, int y)
	{
		_center[0] = x;
		_center[1] = y;
		this->SetXY(this->_center[0] - (this->GetWidth() >> 1), this->_center[1] - (this->GetHeight() >> 2));
	}

	int CGameWeapon::GetCost()
	{
		return _cost;
	}

	CGameWeapon::Type CGameWeapon::GetType()
	{
		return _weaponType;
	}
}