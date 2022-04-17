#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameBullet.h"

namespace game_framework
{
	CGameBullet::CGameBullet()
	{
		_showPriority = 5;
		_damage = 4;
		_target = "";
		CGameBullet::CGameObj::SetTag("bullet");
	}
	/*CGameBullet::CGameBullet(int x, int y)
	{
		_mx = x;
		_my = y;
		_showPriority = 5;
		_damage = 4;
		_target = "";
		CGameBullet::CGameObj::SetTag("bullet");
	}*/

	CGameBullet::CGameBullet(const CGameBullet& other):CGameObj(other)
	{
		_damage = other._damage;
		_target = other._target;
	}

	void CGameBullet::LoadBitmap()
	{
		CGameBullet::CGameObj::_animaIter->AddBitmap(IDB_Bullet0, RGB(255, 255, 255)); //test image
	}

	void CGameBullet::OnMove(CGameMap* map)
	{
		//	�ھ� _vector �i�沾��
		_mx += (int)((double)_moveSpeed * _vector[0]);
		_my += (int)((double)_moveSpeed * _vector[1]);

		//	��Ĳ��a�ϳ��𰱤�Ωж��q�D�s���B
		if (CGameBullet::CGameObj::Collision(map) || CGameBullet::CGameObj::Collision(map, CGameMap::ContentType::AISLEWALL))
			CGameBullet::CGameObj::SetEnable(false);
	}

	/*void CGameBullet::OnShow(CGameMap* map)
	{

	}*/

	void CGameBullet::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		if (other->GetTag() == _target)
		{
			this->SetEnable(false);
			other->TakeDmg(_damage);
		}
	}

	void CGameBullet::SetTarget(string target)
	{
		_target = target;
	}

	void CGameBullet::SetDamage(int damage)
	{
		_damage = damage;
	}

}
