#pragma once
#include "CGameRoom.h"

namespace game_framework {
	class CGameMap
	{
	public:
		enum class MapContent {NULLPTR, FLOOR, WALL, AISLEWALL};		//地圖內容物
		CGameMap();
		void LoadBitmap();
		int ScreenX(int x);				//	地圖點座標在螢幕位置
		int ScreenY(int y);
		bool InScreen(int x, int y, int mw, int mh);	// 座標範圍在螢幕內
		bool IsContent(int x, int y, CGameMap::MapContent = MapContent::FLOOR);

		int GetScreenX();
		int GetScreenY();

		void SetScreen(int x, int y);	

		void OnMove(int x, int y);
		void OnShow();
		void OnKeyUp(char nChar);
		void OnKeyDown(char nChar);
		void GenerateMap();				//	生成地圖
		void Reset();

	protected:
		MapContent _map[200][200];						// 地圖每格內容
		int _sx, _sy, _moveSpeed;						// 螢幕點座標、移動速度			
		vector<CAnimation> _animas;						// 地圖圖片
		vector<CAnimation>::iterator _animaIterator;	// 操作用
		const int _MAPW, _MAPH;							// 地圖每格寬高
		const int _MAXNOFROOM = 4;						// 最大房間數 _MAXNOFROOM * _MAXNOFROOM
		
	
	private:
		vector<CAnimation>::iterator GetAnima(MapContent);
	};
}