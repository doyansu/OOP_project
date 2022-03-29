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
		for (int i = 0; i < (int)_allObj.size(); i++)
		{
			if (_allObj.at(i)->IsEnable())
			{
				_allObj.at(i)->OnMove(map);
			}
			else
			{
				delete _allObj.at(i);
				_allObj.erase(_allObj.begin() + i);
			}
				
		}
			
		for (int i = 0; i < (int)_allObj.size(); i++)
			for (int j = i + 1; j < (int)_allObj.size(); j++)
				if (_allObj.at(i)->Collision(_allObj.at(j)))
				{
					_allObj.at(i)->OnObjCollision(_allObj.at(j));
					_allObj.at(j)->OnObjCollision(_allObj.at(i));
				}
				
	}

	void CGameObjCenter::OnShow(CGameMap* map)
	{
		for (int i = 0; i < (int)_allObj.size(); i++)
		{
			CGameObj* obj = _allObj.at(i);
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
			delete p;
		_allObj.clear();
	}

	

	
	vector<CGameObj*> CGameObjCenter::_allObj;
}