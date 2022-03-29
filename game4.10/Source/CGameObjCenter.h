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
			//_allObj.insert(_allObj.end(), obj);
		}


	protected:

	private:
		static vector<CGameObj*> _allObj;
		void init();
		void freeObj();
		
	};
	
}
