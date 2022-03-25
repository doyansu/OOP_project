#pragma once

namespace game_framework {
	class CGameMap
	{
	public:
		enum class MapContent {NENO, FLOOR, WALL};		//�a�Ϥ��e��
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

		vector<CMovingBitmap> _bmp;						// �a�ϹϤ�
		vector<CMovingBitmap>::iterator _bmpIterator;	// �ާ@��
		const int _MAPW, _MAPH;							// �a�ϨC��e��
		MapContent _map[200][200];						// �a�ϨC�椺�e
		int _sx, _sy, _moveSpeed;						// �ù��I�y�СB���ʳt��
		
		bool _isMovingDown;			
		bool _isMovingLeft;			
		bool _isMovingRight;		
		bool _isMovingUp;			
	
	private:
		void init();
		vector<CMovingBitmap>::iterator GetBmp(MapContent);
	};
}