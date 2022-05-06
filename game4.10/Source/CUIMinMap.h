#pragma once
#include "CGameMap.h"

namespace game_framework
{
	class CUIMinMap
	{
	public:
		enum class Anima { NOTEXPLORED, EXPLORED, PLAYERIN, INIT, TREASURE, BOSS, END, ANIMACOUNT };
		CUIMinMap(RoomData ** = nullptr);
		void SetXY(int, int);

		void LoadBitmap();
		void OnMove();
		void OnShow();

	private:
		int _sx, _sy;									//	�p�a�Ϧb�ù���m
		bool aisle[MYMAXNOFROOM][MYMAXNOFROOM][2];
		RoomData ** _rooms;
		vector<CAnimation> _animas;

		vector<CAnimation>::iterator GetAnima(Anima);

	};
}