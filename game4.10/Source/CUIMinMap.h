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
		int _sx, _sy;									//	�p�a�Ϧb�ù���m
		bool aisle[MYMAXNOFROOM][MYMAXNOFROOM][2];

	};
}