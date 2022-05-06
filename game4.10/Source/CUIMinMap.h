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
		int _sx, _sy;					//	�p�a�Ϧb�ù���m
		int _px, _py;					//	��ܤ���
		RoomData ** _rooms;				//	�ж����	
		vector<CAnimation> _animas;

		vector<CAnimation>::iterator GetAnima(Anima);

	};
}