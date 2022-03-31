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
		// 刪除物件
		for (int i = 0; i < (int)_allObj.size(); i++)
		{
			if (!_allObj.at(i)->IsEnable() && !_allObj.at(i)->IsDie())
			{
				delete _allObj.at(i);
				_allObj.erase(_allObj.begin() + i);
			}
		}

		// 移動物件
		for (CGameObj* obj : _allObj)
		{
			if (obj->IsEnable())
			{
				obj->OnMove(map);
			}
			else if(obj->IsDie())
			{
				obj->OnDie();
			}
		}
		
		// 處理碰撞
		for (int i = 0; i < (int)_allObj.size(); i++)
		{
			if (!_allObj.at(i)->IsEnable())
				continue;
			for (int j = i + 1; j < (int)_allObj.size(); j++)
				if (_allObj.at(j)->IsEnable() && _allObj.at(i)->Collision(_allObj.at(j)))
				{
					_allObj.at(i)->OnObjCollision(_allObj.at(j));
					_allObj.at(j)->OnObjCollision(_allObj.at(i));
				}
		}
			
				
	}

	void CGameObjCenter::OnShow(CGameMap* map)
	{
		for (CGameObj* obj : _allObj)
		{
			if(map->InScreen(obj->GetX1(), obj->GetY1(), obj->GetX2(), obj->GetY2()))
				obj->OnShow(map);
		}
	}

	void CGameObjCenter::FreeALLObj()
	{
		freeObj();
	}

	void CGameObjCenter::freeObj()
	{
		for (CGameObj* p : _allObj)
		{
			if (p->NeedFree())
			{
				delete p;
			}
		}
			
		_allObj.clear();
	}

	

	
	vector<CGameObj*> CGameObjCenter::_allObj;
}