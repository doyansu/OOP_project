#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameWeapon.h"

namespace game_framework
{
	CGameWeapon::CGameWeapon()
	{
		init();
	}

	void CGameWeapon::init()
	{
		_atk, _cost = 0;
		Reset();
	}
		
	void CGameWeapon::Reset()
	{
		CGameObj::Reset();
	}

	void CGameWeapon::LoadBitmap()
	{
		//CGameObj::LoadBitmap(IDB_ERASER1); //test
		CGameWeapon::CGameObj::LoadBitmap(IDB_ERASER1);
	}

	void CGameWeapon::OnMove(CGameMap* map)
	{

	}

	/*void CGameWeapon::OnShow(CGameMap* map)
	{

	}*/

	void CGameWeapon::Shoot(CGameObj* player)
	{

	}
}