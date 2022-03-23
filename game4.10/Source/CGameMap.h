#pragma once

namespace game_framework {
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitmap();
		int ScreenX(int x);
		int ScreenY(int y);
		void SetMovingDown(bool flag);	
		void SetMovingLeft(bool flag);	
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);	
		void OnMove();
		void OnShow();
		void OnKeyUp(char);
		void OnKeyDown(char);
		void GenerateMap();

	protected:

		CMovingBitmap _floor, _wall;
		int _map[200][200];
		int _sx, _sy, _moveSpeed;
		const int _MW, _MH;

		bool _isMovingDown;			
		bool _isMovingLeft;			
		bool _isMovingRight;		
		bool _isMovingUp;			
	
	private:
		void init();
	};
}