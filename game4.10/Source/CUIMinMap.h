#pragma once
#include "CGameMap.h"
#define MINMAPSIZE 3
#define MINMAPINTERNAL 25

namespace game_framework
{
	class CUIMinMap
	{
	public:
		enum class Anima { NOTEXPLORED, EXPLORED, PLAYERIN, INIT, TREASURE, BOSS, END, AILSES, AILSEH, ANIMACOUNT };
		CUIMinMap();
		void SetXY(int, int);
		void SetRoom(RoomData **);
		void PlayerIn(int, int);

		void LoadBitmap();
		void OnMove();
		void OnShow();

	private:
		int _sx, _sy;					//	小地圖在螢幕位置
		int _px, _py;					//	顯示中心
		RoomData ** _rooms;				//	房間資料	
		vector<CAnimation> _animas;

		vector<CAnimation>::iterator GetAnima(Anima);

	};
}