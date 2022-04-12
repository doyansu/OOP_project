#pragma once
#include <queue>
#include <cmath>

#define MYMAPSIZE 250		// 地圖格數大小 250 X 250
#define MYMAPWIDTH 25		// 地圖每格寬
#define MYMAPHIGH 25		// 地圖每格高
#define MYMAXNOFROOM 7		// 最大房間數 7 X 7
#define ROOMINTERNAL 35		// 房間中心的間隔距離
#define MYORGROOM 3			// 中心點起始房間

namespace game_framework {
	class RoomData
	{
	friend class CGameMap;
	public:
		enum class RoomType { INIT, NORMAL, TREASURE, END };
		RoomData();
		int CenterX();
		int CenterY();
		int Width();
		int High();
		bool HasRoad(int);
		RoomData::RoomType GetRoomType();

	protected:
		bool _hasRoom;					// 有房間
		bool _hasRoad[4];				// 上下左右有通道
		int _centerX, _centerY;		// 中心位置
		int _width, _high;			// 寬高
		RoomData::RoomType _roomType;	// 房間類型
	};

	class CGameMap
	{
	public:
		enum class MapContent {NULLPTR, FLOOR, WALL, AISLEWALL};		//地圖內容物
		CGameMap();
		~CGameMap();
		void LoadBitmap();
		int ScreenX(int x);				//	地圖點座標在螢幕位置
		int ScreenY(int y);
		bool InScreen(int x, int y, int mw, int mh);	// 座標範圍在螢幕內
		bool IsContent(int x, int y, CGameMap::MapContent = MapContent::FLOOR);

		int GetScreenX();
		int GetScreenY();
		RoomData GetRoom(int, int);

		void SetScreen(int x, int y);	

		void OnMove(int x, int y);
		void OnShow();
		void OnKeyUp(char nChar);
		void OnKeyDown(char nChar);
		void GenerateMap();				//	生成地圖
		void Reset();

	protected:
		CGameMap::MapContent _map[MYMAPSIZE][MYMAPSIZE];			
		int _sx, _sy, _moveSpeed;						// 螢幕點座標、移動速度			
		vector<CAnimation> _animas;						// 地圖圖片
		vector<CAnimation>::iterator _animaIterator;	// 操作用
		const int _MAPW, _MAPH;							// 地圖每格寬高
		const int _MAXNOFROOM;							// 最大房間數 _MAXNOFROOM * _MAXNOFROOM
		RoomData** _Rooms;								// 房間資料
		
	
	private:
		void free();
		vector<CAnimation>::iterator GetAnima(MapContent);
		class Point
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