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
		const int _MAPW, _MAPH;				//�a�ϨC��e��
		const int _SCREENW, _SCREENH;				//�ù��e��
		int _map[200][200];				//�a�ϨC�椺�e
		int _sx, _sy, _moveSpeed;		//�ù��I�y�СB���ʳt��
		
		bool _isMovingDown;			
		bool _isMovingLeft;			
		bool _isMovingRight;		
		bool _isMovingUp;			
	
	private:
		void init();
	};
}