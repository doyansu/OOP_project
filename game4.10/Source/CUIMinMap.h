#pragma once
#include "CGameMap.h"

namespace game_framework
{
	class CUIMinMap
	{
	public:
		CUIMinMap();
		SetXY(int, int);
		OnShow();

	private:
		int _sx, _sy;									//	小地圖在螢幕位置
		bool aisle[MYMAXNOFROOM][MYMAXNOFROOM][2];

	};
}