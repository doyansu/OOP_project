#pragma once

namespace game_framework {
	class CGameMap
	{
	public:
		enum class MapContent {NENO, FLOOR, WALL};		//地圖內容物
		CGameMap();
		void LoadBitmap();
		int ScreenX(int x);
		int ScreenY(int y);
		bool InScreen(int x, int y, int mw, int mh);
		bool IsEmpty(int x, int y);

		int GetScreenX();
		int GetScreenY();

		void SetScreen(int x, int y);
		void SetMovingDown(bool flag);	
		void SetMovingLeft(bool flag);	
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);	

		void OnMove(int x, int y);
		void OnShow();
		void OnKeyUp(char nChar);
		void OnKeyDown(char nChar);
		void GenerateMap();
		void Reset();

	protected:

		vector<CMovingBitmap> _bmp;						// 地圖圖片
		vector<CMovingBitmap>::iterator _bmpIterator;	// 操作用
		const int _MAPW, _MAPH;							// 地圖每格寬高
		MapContent _map[200][200];						// 地圖每格內容
		int _sx, _sy, _moveSpeed;						// 螢幕點座標、移動速度
		
		bool _isMovingDown;			
		bool _isMovingLeft;			
		bool _isMovingRight;		
		bool _isMovingUp;			
	
	private:
		void init();
		vector<CMovingBitmap>::iterator GetBmp(MapContent);
	};
}