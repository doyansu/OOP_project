#pragma once


namespace game_framework {
	class CGameMap
	{
	public:
		enum class MapContent {NULLPTR, FLOOR, WALL};		//�a�Ϥ��e��
		CGameMap();
		void LoadBitmap();
		int ScreenX(int x);				//	�a���I�y�Цb�ù���m
		int ScreenY(int y);
		bool InScreen(int x, int y, int mw, int mh);	// �y�нd��b�ù���
		bool IsEmpty(int x, int y);

		int GetScreenX();
		int GetScreenY();

		void SetScreen(int x, int y);	

		void OnMove(int x, int y);
		void OnShow();
		void OnKeyUp(char nChar);
		void OnKeyDown(char nChar);
		void GenerateMap();				//	�ͦ��a��
		void Reset();

	protected:

		vector<CAnimation> _animas;						// �a�ϹϤ�
		vector<CAnimation>::iterator _animaIterator;	// �ާ@��
		const int _MAPW, _MAPH;							// �a�ϨC��e��
		MapContent _map[200][200];						// �a�ϨC�椺�e
		int _sx, _sy, _moveSpeed;						// �ù��I�y�СB���ʳt��			
	
	private:
		void init();
		vector<CAnimation>::iterator GetAnima(MapContent);
	};
}