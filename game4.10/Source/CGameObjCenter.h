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
			game_framework::CGameObjCenter::_allObj.push_back(obj);
		}


	protected:
		static vector<CGameObj*> _allObj;

	private:
		void init();
		void freeObj();
		
	};
	vector<CGameObj*> CGameObjCenter::_allObj;
}
