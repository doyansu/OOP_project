#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameWeapon.h"


namespace game_framework
{
	CGameWeapon::CGameWeapon(CGameObj* user)
	{
		// 動畫載入
		const int AnimaSize = 2;
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
		_DT = 1;
		CGameWeapon::CGameObj::SetTag("weapon");
		// 子彈設定
		//_bullet = new CGameBullet(this->CenterX(), this->CenterY());
		_bullet = new CGameBullet(this->GetX1(), this->GetY1());
		//_bullet->SetXY(this->CenterX(), this->CenterY());
		_bullet->SetSpeed(_bulletSpeed);
	}

	CGameWeapon::~CGameWeapon()
	{
		free();
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
		this->_bullet = new CGameBullet(*(other._bullet));
		this->_user = other._user;
	}

	void CGameWeapon::free()
	{
		delete _bullet;
		_bullet = nullptr;
	}

	void CGameWeapon::LoadBitmap()
	{
		CGameWeapon::CGameObj::_animaIter = GetAnima(CGameWeapon::Anima::Right);
		CGameWeapon::CGameObj::_animaIter->AddBitmap(IDB_weapon1, RGB(255, 255, 255));
				
		CGameWeapon::CGameObj::_animaIter = GetAnima(CGameWeapon::Anima::Left);
		CGameWeapon::CGameObj::_animaIter->AddBitmap(IDB_weapon1_l, RGB(255, 255, 255));

		CGameWeapon::CGameObj::_animaIter = GetAnima(CGameWeapon::Anima::Right);

		_bullet->LoadBitmap();
	}

	void CGameWeapon::OnMove(CGameMap* map)
	{
		CGameWeapon::CGameObj::_animaIter->OnMove();

		if (_user == nullptr)
			return;
		
		if (_DT == 1) {
			this->SetXY(_user->CenterX(), _user->CenterY());
		}
		else if (_DT == 0) {
			this->SetXY(_user->CenterX() - (this->GetX2() - this->GetX1()), _user->CenterY());
		}

		//	射擊間隔計數
		if (!_fire && --_fireCounter == 0)
			_fire = true;
		
		// debug
		/*if (_mx < 0 || _my < 0 || _mx > MYMAPSIZE * MYMAPSIZE || _my > MYMAPSIZE * MYMAPSIZE)
			GAME_ASSERT(false, "武器超出地圖!");*/
	}

	void CGameWeapon::OnShow(CGameMap* map)
	{
		CGameWeapon::CGameObj::OnShow(map);
	}

	void CGameWeapon::Shoot(double x, double y)
	{
		if (_fire)
		{
			/*if(_DT == 0) // 從槍口開槍
				_bullet.SetXY(this->GetX1(), this->CenterY());
			else if (_DT == 1)
				_bullet.SetXY(this->GetX2(), this->CenterY());*/
			_bullet->SetXY(this->CenterX(), this->CenterY());
			_bullet->SetVector(x, y);
			CGameObjCenter::AddObj(new CGameBullet(*_bullet));
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
		// 動畫判斷
		if (_DT == 1) {
			CGameWeapon::CGameObj::_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Right);
		}
		else if (_DT == 0) {
			CGameWeapon::CGameObj::_animaIter = CGameWeapon::GetAnima(CGameWeapon::Anima::Left);
		}
	}

	void CGameWeapon::SetTarget(string target)
	{
		_bullet->SetTarget(target);
	}

	void CGameWeapon::SetUser(CGameObj* user)
	{
		_user = user;
	}

	void CGameWeapon::SetAttributes(int atk, int cost, int bulletSpeed, int shootDelay)
	{
		_cost = cost;
		_bulletSpeed = bulletSpeed;
		_shootDelay = shootDelay;
		_bullet->SetSpeed(_bulletSpeed);
		_bullet->SetDamage(atk);
	}
}