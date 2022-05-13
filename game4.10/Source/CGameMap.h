#pragma once
#include <queue>
#include <cmath>
#include "CGameTool.h"

#define MYMAXNOFROOM 7								// 最大房間數 7 X 7
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
		enum class RoomType { NOROOM, INIT, NORMAL, TREASURE, SPECIAL, BOSS, END };
		RoomData();
		int CenterX();
		int CenterY();
		int Width();
		int High();
		bool HasRoad(int);
		bool IsExplored();
		bool PlayerIn();
		void SetExplored(bool);
		void SetPlayerIn(bool);
		RoomData::RoomType GetRoomType();

	protected:
		bool _hasRoom;					// 有房間
		bool _explored;					// 有無探索過
		bool _playerIn;					// 玩家是否在房間
		bool _hasRoad[4];				// 上下左右有通道
		int _centerX, _centerY;			// 在地圖中心位置
		int _width, _high;				// 寬高
		RoomData::RoomType _roomType;	// 房間類型
	};

	class CGameMap
	{
	public:
		enum class ContentType { NULLPTR, FLOOR, WALL, AISLEWALL, WALLBOTTOM };		//地圖內容物類型
		CGameMap();
		~CGameMap();
		void LoadBitmap();
		int ScreenX(int x);				//	地圖點座標在螢幕位置
		int ScreenY(int y);
		bool InScreen(int x, int y, int mw, int mh);	// 座標範圍在螢幕內
		bool IsContent(int x, int y, CGameMap::ContentType = CGameMap::ContentType::FLOOR);

		int GetScreenX();
		int GetScreenY();
		RoomData* GetRoom(int, int);
		RoomData** GetRooms();

		void SetScreen(int x, int y);	
		void ModifyDsx(int);
		void ModifyDsy(int);

		void OnMove(int x, int y);
		void OnShow(bool cover = false);
		void OnKeyUp(char nChar);
		void OnKeyDown(char nChar);
		void GenerateMap(bool hasBOSS = false);				//	生成地圖
		void Reset();

	protected:
		class MapContent	
		{
		friend class CGameMap;
		public:
			MapContent()
			{
				_type = CGameMap::ContentType::NULLPTR;
				_cover = _show  = false;
			}
			MapContent(CGameMap::ContentType type, vector<CAnimation>::iterator anima, bool cover = false, bool show = false)
			{
				_type = type;
				_anima = anima;
				_cover = cover;
				_show = show;
			}
			
			bool IsType(CGameMap::ContentType type)// 好像有 bug 會在這邊中斷 (4/16 更新地圖實作開始) (4/30 補充已修正)
			{
				return _type == type;
			}
			bool IsCover()
			{
				return _cover;
			}
			bool IsShow()
			{
				return _show;
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
			bool _cover, _show;						//	是否覆蓋物件、是否特殊顯示
		private:
		};
		CGameMap::MapContent _map[MYMAPSIZE][MYMAPSIZE];			
		int _sx, _sy, _moveSpeed;						// 螢幕點座標、移動速度	
		int _dsx, _dsy;									// 螢幕位置偏移量
		vector<vector<CAnimation>> _animas;				// 地圖動畫
		const int _MAPW, _MAPH;							// 地圖每格寬高
		const int _MAXNOFROOM;							// 最大房間數 _MAXNOFROOM * _MAXNOFROOM
		RoomData** _Rooms;								// 房間資料
		
	
	private:
		void free();
		void normalRoomGenerate(int, int);
		vector<CAnimation>::iterator GetAnima(CGameMap::ContentType, int=-1);
		CGameTool::Point* _roomTree;
	};
}