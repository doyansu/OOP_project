#pragma once

#include "CGameObj.h"

namespace game_framework {
	class CGameMap : public CGameObj
	{
	public:
		CGameMap();
		void LoadBitmap();
		void OnMove();
		void OnShow();

	protected:
		CMovingBitmap _floor;
		int _map[100][100];
		const int _X, _Y;
		const int _MW, _MH;
	};
}