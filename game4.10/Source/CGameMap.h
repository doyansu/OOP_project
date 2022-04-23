#pragma once
#include <queue>
#include <cmath>

#define MYMAXNOFROOM 9								// �̤j�ж��� 9 X 9
#define ROOMINTERNAL 35								// �ж����ߪ����j�Z��
#define MYMAPSIZE MYMAXNOFROOM * ROOMINTERNAL		// �a�Ϯ�Ƥj�p 
#define MYMAPWIDTH 25								// �a�ϨC��e
#define MYMAPHIGH 25								// �a�ϨC�氪
#define MYORGROOM (MYMAXNOFROOM>>1)					// �����I�_�l�ж�

namespace game_framework {
	class RoomData
	{
	friend class CGameMap;
	public:
		enum class RoomType { NOROOM, INIT, NORMAL, TREASURE, BOSS, END };
		RoomData();
		int CenterX();
		int CenterY();
		int Width();
		int High();
		bool HasRoad(int);
		RoomData::RoomType GetRoomType();

	protected:
		bool _hasRoom;					// ���ж�
		bool _hasRoad[4];				// �W�U���k���q�D
		int _centerX, _centerY;		// ���ߦ�m
		int _width, _high;			// �e��
		RoomData::RoomType _roomType;	// �ж�����
	};

	class CGameMap
	{
	public:
		enum class ContentType {NULLPTR, FLOOR, WALL, AISLEWALL};		//�a�Ϥ��e������
		CGameMap();
		~CGameMap();
		void LoadBitmap();
		int ScreenX(int x);				//	�a���I�y�Цb�ù���m
		int ScreenY(int y);
		bool InScreen(int x, int y, int mw, int mh);	// �y�нd��b�ù���
		bool IsContent(int x, int y, CGameMap::ContentType = CGameMap::ContentType::FLOOR);

		int GetScreenX();
		int GetScreenY();
		RoomData GetRoom(int, int);

		void SetScreen(int x, int y);	

		void OnMove(int x, int y);
		void OnShow();
		void OnKeyUp(char nChar);
		void OnKeyDown(char nChar);
		void GenerateMap();				//	�ͦ��a��
		void Reset();

	protected:
		class MapContent	
		{
		friend class CGameMap;
		public:
			MapContent()
			{
				_type = CGameMap::ContentType::NULLPTR;
			}
			MapContent(CGameMap::ContentType type, vector<CAnimation>::iterator anima)
			{
				_type = type;
				_anima = anima;
			}
			
			bool IsType(CGameMap::ContentType type)// �n���� bug �|�b�o�䤤�_ (4/16 ��s�a�Ϲ�@�}�l)
			{
				return _type == type;
			}

			CGameMap::ContentType GetType()
			{
				return _type;
			}
			vector<CAnimation>::iterator GetAnima()
			{
				return _anima;
			}
		protected:
			CGameMap::ContentType _type;
			vector<CAnimation>::iterator _anima;
		private:
		};

		CGameMap::MapContent _map[MYMAPSIZE][MYMAPSIZE];			
		int _sx, _sy, _moveSpeed;						// �ù��I�y�СB���ʳt��			
		vector<vector<CAnimation>> _animas;						// �a�ϰʵe
		const int _MAPW, _MAPH;							// �a�ϨC��e��
		const int _MAXNOFROOM;							// �̤j�ж��� _MAXNOFROOM * _MAXNOFROOM
		RoomData** _Rooms;								// �ж����
		
	
	private:
		void free();
		void normalRoomGenerate(int, int);
		vector<CAnimation>::iterator GetAnima(CGameMap::ContentType, int=-1);
		
		class Point	// �a�ϥͦ��ϥ�
		{
		public:
			Point()
			{
				_xy[0] = _xy[1] = 0;
			}

			Point(int x, int y)
			{
				_xy[0] = x;
				_xy[1] = y;
			}

			void Set(int index, int value)
			{
				if (index > 1 || index < 0)
					ASSERT(0);
				_xy[index] = value;
			}

			int Get(int index)
			{
				if (index > 1 || index < 0)
					ASSERT(0);
				return _xy[index];
			}

		private:
			int _xy[2];
		};
	};
}