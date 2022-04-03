#pragma once

#define MYMAPSIZE 200		// 地圖格數大小 200 X 200
#define MYMAPWIDTH 25		// 地圖每格寬
#define MYMAPHIGH 25		// 地圖每格高
#define MYMAXNOFROOM 4		// 最大房間數 4 X 4

namespace game_framework {
	class RoomData
	{
	friend class CGameMap;
	public:
		RoomData();
		int CenterX();
		int CenterY();
		int Width();
		int High();

	protected:
		bool __hasRoom;				// 有房間
		bool __hasRoad[4];			// 上下左右有通道
		int __centerX, __centerY;	// 中心位置
		int __width, __high;		// 寬高
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
		MapContent _map[MYMAPSIZE][MYMAPSIZE];			// 地圖每格內容 200 X 200
		int _sx, _sy, _moveSpeed;						// 螢幕點座標、移動速度			
		vector<CAnimation> _animas;						// 地圖圖片
		vector<CAnimation>::iterator _animaIterator;	// 操作用
		const int _MAPW, _MAPH;							// 地圖每格寬高
		const int _MAXNOFROOM;							// 最大房間數 _MAXNOFROOM * _MAXNOFROOM
		RoomData** _Rooms;								// 房間資料
		
	
	private:
		void free();
		vector<CAnimation>::iterator GetAnima(MapContent);
	};
}