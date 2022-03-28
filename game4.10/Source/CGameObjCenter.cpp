#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameObjCenter.h"

namespace game_framework
{
	CGameObjCenter::CGameObjCenter()
	{
		init();
	}

	CGameObjCenter::~CGameObjCenter()
	{
		freeObj();
	}

	void CGameObjCenter::init()
	{
		_allObj.reserve(1024);
	}

	void CGameObjCenter::OnMove(CGameMap* map)
	{
		for (CGameObj* obj : _allObj)
			obj->OnMove(map);
		for (CGameObj* obj : _allObj)
			for (CGameObj* other : _allObj)
				if (obj->Collision(other))
				{
					obj->OnObjCollision(other);
					other->OnObjCollision(obj);
				}

	}

	void CGameObjCenter::OnShow(CGameMap* map)
	{
		for (CGameObj* obj : _allObj)
			obj->OnShow(map);
	}

	void CGameObjCenter::FreeALLObj()
	{
		freeObj();
	}

	void CGameObjCenter::freeObj()
	{
		for (CGameObj* p : _allObj)
			delete p;
		_allObj.clear();
	}

	

	

}