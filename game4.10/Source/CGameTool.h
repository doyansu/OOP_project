#pragma once

namespace game_framework
{
	class CGameTool	// 工具函式、類別定義
	{
	public:

		// function
		template<typename condition, typename source>	// 依條件尋找單個物件
		static source FindObjBy(vector<source> objs, condition function)
		{
			for (source obj : objs)
			{
				if (function(obj))
					return obj;
			}
			return nullptr;
		}

		template<typename condition, typename source>	// 依條件尋找多個物件
		static vector<source> FindObjsBy(vector<source> objs, condition function)
		{
			vector<source> result;
			result.reserve(objs.capacity());
			for (CGameObj* obj : objs)
			{
				if (function(obj))
					result.push_back(obj);
			}
			return result;
		}

		template<typename compare, typename source>	//	依比較函式找到最符合物件
		static vector<source> FindMaxObjBy(vector<source> objs, compare cmp)
		{
			source maxObj = objs.begin();
			for (CGameObj* obj : objs)
			{
				if (cmp(maxObj, obj))
					maxObj = obj;
			}
			return maxObj;
		}

		// class
		class Point	// 紀錄2點座標
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


	};
}


