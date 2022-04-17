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
		_allObj.reserve(256);
		_temp.reserve(256);
	}

	void CGameObjCenter::OnMove(CGameMap* map)
	{
		// �[�J����
		if ((int)_temp.size() > 0)
		{
			for (CGameObj* obj : _temp)
				_allObj.push_back(obj);
			std::sort(_allObj.begin(), _allObj.end(),
				[](CGameObj* a, CGameObj* b)
			{
				return a->GetShowPriority() < b->GetShowPriority();
			});
			_temp.clear();
		}
		

		// �R������
		for (int i = 0; i < (int)_allObj.size(); i++)
		{
			if (!_allObj.at(i)->IsEnable() && !_allObj.at(i)->IsDie())
			{
				delete _allObj.at(i);
				_allObj.erase(_allObj.begin() + i);
			}
		}

		// ���ʡB�s�W����
		for (int i = 0; i < (int)_allObj.size(); i++)
		{
			CGameObj* obj = _allObj.at(i);
			if (obj->IsEnable())
			{
				obj->OnMove(map);

				// debug
				int x = obj->GetX1();
				int y = obj->GetY1();
				if (x < 0 || y < 0 || x > MYMAPSIZE * MYMAPSIZE || y > MYMAPSIZE * MYMAPSIZE)
				{
					obj->SetEnable(false);
					obj->SetDie(false);
					//GAME_ASSERT(fasle, "����W�X�a��!");
				}
			}
			else if(obj->IsDie())
			{
				obj->OnDie();
			}
		}
		
		// �B�z�I��
		for (int i = 0; i < (int)_allObj.size(); i++)
		{
			if (!_allObj.at(i)->IsEnable())
				continue;
			for (int j = i + 1; j < (int)_allObj.size(); j++)
				if (_allObj.at(j)->IsEnable() && _allObj.at(i)->Collision(_allObj.at(j)))
				{
					_allObj.at(i)->OnObjCollision(map, _allObj.at(j));
					_allObj.at(j)->OnObjCollision(map, _allObj.at(i));
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
		_temp.clear();
		_allObj.clear();
	}


	vector<CGameObj*> CGameObjCenter::_allObj, CGameObjCenter::_temp;
}