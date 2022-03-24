#pragma once

namespace game_framework {
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitmap();
		int ScreenX(int x);
		int ScreenY(int y);
		bool InScreen(int x, int y, int mw, int mh);
		void SetMovingDown(bool flag);	
		void SetMovingLeft(bool flag);	
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);	
		void OnMove();
		void OnShow();
		void OnKeyUp(char nChar);
		void OnKeyDown(char nChar);
		void GenerateMap();
		void Reset();

	protected:

		CMovingBitmap _floor, _wall;
		const int _MAPW, _MAPH;				//地圖每格寬高
		const int _SCREENW, _SCREENH;				//螢幕寬高
		int _map[200][200];				//地圖每格內容
		int _sx, _sy, _moveSpeed;		//螢幕點座標、移動速度
		
		bool _isMovingDown;			
		bool _isMovingLeft;			
		bool _isMovingRight;		
		bool _isMovingUp;			
	
	private:
		void init();
	};
}