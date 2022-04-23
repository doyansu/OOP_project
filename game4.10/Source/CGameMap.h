#pragma once
#include <queue>
#include <cmath>

#define MYMAXNOFROOM 9								// 最大房間數 9 X 9
#define ROOMINTERNAL 35								// 房間中心的間隔距離
#define MYMAPSIZE MYMAXNOFROOM * ROOMINTERNAL		// 地圖格數大小 
#define MYMAPWIDTH 25								// 地圖每格寬
#define MYMAPHIGH 25								// 地圖每格高
#define MYORGROOM (MYMAXNOFROOM>>1)					// 中心點起始房間

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
		bool _hasRoom;					// 有房間
		bool _hasRoad[4];				// 上下左右有通道
		int _centerX, _centerY;		// 中心位置
		int _width, _high;			// 寬高
		RoomData::RoomType _roomType;	// 房間類型
	};

	class CGameMap
	{
	public:
		enum class ContentType {NULLPTR, FLOOR, WALL, AISLEWALL};		//地圖內容物類型
		CGameMap();
		~CGameMap();
		void LoadBitmap();
		int ScreenX(int x);				//	地圖點座標在螢幕位置
		int ScreenY(int y);
		bool InScreen(int x, int y, int mw, int mh);	// 座標範圍在螢幕內
		bool IsContent(int x, int y, CGameMap::ContentType = CGameMap::ContentType::FLOOR);

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
			
			bool IsType(CGameMap::ContentType type)// 好像有 bug 會在這邊中斷 (4/16 更新地圖實作開始)
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
		int _sx, _sy, _moveSpeed;						// 螢幕點座標、移動速度			
		vector<vector<CAnimation>> _animas;						// 地圖動畫
		const int _MAPW, _MAPH;							// 地圖每格寬高
		const int _MAXNOFROOM;							// 最大房間數 _MAXNOFROOM * _MAXNOFROOM
		RoomData** _Rooms;								// 房間資料
		
	
	private:
		void free();
		void normalRoomGenerate(int, int);
		vector<CAnimation>::iterator GetAnima(CGameMap::ContentType, int=-1);
		
		class Point	// 地圖生成使用
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