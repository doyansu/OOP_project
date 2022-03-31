#pragma once


namespace game_framework {
	class CGameMap
	{
	public:
		enum class MapContent {NULLPTR, FLOOR, WALL};		//地圖內容物
		CGameMap();
		void LoadBitmap();
		int ScreenX(int x);				//	地圖點座標在螢幕位置
		int ScreenY(int y);
		bool InScreen(int x, int y, int mw, int mh);	// 座標範圍在螢幕內
		bool IsEmpty(int x, int y);

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

		vector<CAnimation> _animas;						// 地圖圖片
		vector<CAnimation>::iterator _animaIterator;	// 操作用
		const int _MAPW, _MAPH;							// 地圖每格寬高
		MapContent _map[200][200];						// 地圖每格內容
		int _sx, _sy, _moveSpeed;						// 螢幕點座標、移動速度			
	
	private:
		void init();
		vector<CAnimation>::iterator GetAnima(MapContent);
	};
}