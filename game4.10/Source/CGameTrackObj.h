#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameTrackObj : public CGameObj
	{
	public:
		enum class TYPE { GOLD, ENERGYBALL, TYPECOUNT };

		void SetTarget(CGameObj*);
		void SetXY(int, int);

		void LoadBitmap();									
		void OnMove(CGameMap*);
		void OnDie(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);

		static CGameTrackObj* CreateObj(int i)
		{
			static CGameTrackObj _trackObjs[(int)TYPE::TYPECOUNT];
			static bool isLoad = false;
			if (isLoad == false)
			{
				for (int i = 0; i < (int)TYPE::TYPECOUNT; i++)
				{
					_trackObjs[i] = CGameTrackObj((CGameTrackObj::TYPE)i);
					_trackObjs[i].LoadBitmap();
				}
				isLoad = true;
			}
			GAME_ASSERT(i >= 0 && i < (int)TYPE::TYPECOUNT, "create error");
			return new CGameTrackObj(_trackObjs[i]);
		}

	protected:
		CGameObj* _target;
		TYPE _type;
		int _counter;

	private:
		CGameTrackObj(TYPE = TYPE::GOLD);
	};
}


