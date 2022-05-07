#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameTrackObj : public CGameObj
	{
	public:
		enum class TYPE { GOLD, ENERGYBALL };
		CGameTrackObj(TYPE=TYPE::GOLD);

		void SetTarget(CGameObj*);

		void LoadBitmap();									
		void OnMove(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);

	protected:
		CGameObj* _target;
		TYPE _type;
		int _counter;

	private:
	};
}


