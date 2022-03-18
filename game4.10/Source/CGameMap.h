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
		void GenerateMap();

	protected:
		CMovingBitmap _floor, _wall;
		int _map[200][200];
		const int _X, _Y;
		const int _MW, _MH;
	
	private:
		void init();
	};
}