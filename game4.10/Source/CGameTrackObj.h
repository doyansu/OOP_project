#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameTrackObj : public CGameObj
	{
	public:
		enum class TYPE { GOLD, ENERGYBALL, TYPECOUNT };
		CGameTrackObj(TYPE=TYPE::GOLD);

		void SetTarget(CGameObj*);

		void LoadBitmap();									
		void OnMove(CGameMap*);
		void OnDie(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);

		static void Init()
		{
			for (int i = 0; i < (int)TYPE::TYPECOUNT; i++)
			{
				_trackObjs[i] = CGameTrackObj((CGameTrackObj::TYPE)i);
				_trackObjs[i].LoadBitmap();
			}
		}
		static CGameTrackObj* CreateObj(int i)
		{
			GAME_ASSERT(i >= 0 && i < (int)TYPE::TYPECOUNT, "create error");
			return new CGameTrackObj(_trackObjs[i]);
		}

	protected:
		CGameObj* _target;
		TYPE _type;
		int _counter;

		static CGameTrackObj _trackObjs[(int)TYPE::TYPECOUNT];

	private:
	};
}


