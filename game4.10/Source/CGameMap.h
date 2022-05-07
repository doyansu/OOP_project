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
		bool IsExplored();
		bool PlayerIn();
		void SetExplored(bool);
		void SetPlayerIn(bool);
		RoomData::RoomType GetRoomType();

	protected:
		bool _hasRoom;					// ���ж�
		bool _explored;					// ���L�����L
		bool _playerIn;					// ���a�O�_�b�ж�
		bool _hasRoad[4];				// �W�U���k���q�D
		int _centerX, _centerY;			// �b�a�Ϥ��ߦ�m
		int _width, _high;				// �e��
		RoomData::RoomType _roomType;	// �ж�����
	};

	class Point	// ����2�I�y��
	{
	public:
		Point()
		{
			_xy[0] = _xy[1] = 0;
			_childs.reserve(3);
			_parent = nullptr;
		}

		Point(int x, int y)
		{
			_xy[0] = x;
			_xy[1] = y;
			_childs.reserve(3);
			_parent = nullptr;
		}

		void Set(int index, int value)
		{
			if (index > 1 || index < 0)
				ASSERT(0);
			_xy[index] = value;
		}

		void SetParent(Point* parent)
		{
			_parent = parent;
		}

		void AddChild(Point* child)
		{
			_childs.push_back(child);
		}

		int Get(int index)
		{
			if (index > 1 || index < 0)
				ASSERT(0);
			return _xy[index];
		}

		Point* GetParent()
		{
			return _parent;
		}

		vector<Point*> GetChilds()
		{
			return _childs;
		}

		void freeTree()
		{
			for (Point* child : _childs)
			{
				child->freeTree();
			}
			delete this;
		}

		void Travel()
		{
			for (Point* child : _childs)
			{
				child->freeTree();
			}
		}

		bool operator!=(const Point& other)
		{
			return (this->_xy[0] != other._xy[0] || this->_xy[1] != other._xy[1]);
		}

		bool operator==(const Point& other)
		{
			return (this->_xy[0] == other._xy[0] && this->_xy[1] == other._xy[1]);
		}

	private:
		int _xy[2];
		Point* _parent;
		vector<Point*> _childs;
	};

	class CGameMap
	{
	public:
		enum class ContentType { NULLPTR, FLOOR, WALL, AISLEWALL, WALLBOTTOM };		//�a�Ϥ��e������
		CGameMap();
		~CGameMap();
		void LoadBitmap();
		int ScreenX(int x);				//	�a���I�y�Цb�ù���m
		int ScreenY(int y);
		bool InScreen(int x, int y, int mw, int mh);	// �y�нd��b�ù���
		bool IsContent(int x, int y, CGameMap::ContentType = CGameMap::ContentType::FLOOR);

		int GetScreenX();
		int GetScreenY();
		RoomData* GetRoom(int, int);
		RoomData** GetRooms();

		void SetScreen(int x, int y);	

		void OnMove(int x, int y);
		void OnShow(bool cover = false);
		void OnKeyUp(char nChar);
		void OnKeyDown(char nChar);
		void GenerateMap(bool hasBOSS = false);				//	�ͦ��a��
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
			
			bool IsType(CGameMap::ContentType type)// �n���� bug �|�b�o�䤤�_ (4/16 ��s�a�Ϲ�@�}�l) (4/30 �ɥR�w�ץ�)
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
			bool _cover, _show;						//	�O�_�л\����B�O�_�S�����
		private:
		};
		CGameMap::MapContent _map[MYMAPSIZE][MYMAPSIZE];			
		int _sx, _sy, _moveSpeed;						// �ù��I�y�СB���ʳt��			
		vector<vector<CAnimation>> _animas;				// �a�ϰʵe
		const int _MAPW, _MAPH;							// �a�ϨC��e��
		const int _MAXNOFROOM;							// �̤j�ж��� _MAXNOFROOM * _MAXNOFROOM
		RoomData** _Rooms;								// �ж����
		
	
	private:
		void free();
		void normalRoomGenerate(int, int);
		vector<CAnimation>::iterator GetAnima(CGameMap::ContentType, int=-1);
		Point* _roomTree;
	};
}