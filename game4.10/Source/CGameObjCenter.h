#pragma once

#include "CGameObj.h"

namespace game_framework
{
	class CGameObjCenter
	{
	public:
		CGameObjCenter();
		~CGameObjCenter();

		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);
		void FreeALLObj();

		static void CGameObjCenter::AddObj(CGameObj* obj)
		{
			CGameObjCenter::_allObj.push_back(obj);
		}

		template<typename condition>
		static CGameObj* FindObjBy(condition function)
		{
			for (CGameObj* obj : _allObj)
			{
				if (function(obj))
					return obj;
			}
			return nullptr;
		}

		template<typename condition>
		static vector<CGameObj*> FindObjsBy(condition function)
		{
			vector<CGameObj*> objs;
			objs.reserve(_allObj.capacity());
			for (CGameObj* obj : _allObj)
			{
				if (function(obj))
					objs.push_back(obj);
			}
			return objs;
		}

		template<typename compare>
		static vector<CGameObj*> FindMaxObjBy(compare cmp)
		{
			CGameObj* maxObj = _allObj.begin();
			for (CGameObj* obj : _allObj)
			{
				if (cmp(maxObj, obj))
					maxObj = obj;
			}
			return maxObj;
		}

	protected:

	private:
		static vector<CGameObj*> _allObj;
		void init();
		void freeObj();
		
	};
	
}
