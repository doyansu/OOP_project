#ifndef CGAMEOBJ_H
#define CGAMEOBJ_H

#include "CGameMap.h"
#include "CGameTool.h"


namespace game_framework {

	class CGameObj
	{
	public:
		CGameObj();
		CGameObj(const CGameObj& other);
		virtual ~CGameObj();

		// 判斷
		bool Collision(CGameObj*);		// 物件碰撞
		bool Collision(CGameMap*, CGameMap::ContentType = CGameMap::ContentType::WALL);		// 地圖碰撞
		bool IsEnable();				// 是否啟用
		bool NeedFree();				// 是否釋放
		bool IsDie();					// 是否死亡
		bool IsCollision();				// 是否啟用碰撞
		bool IsLoad();					// 是否已執行 LoadBitmap()

		// Getter
		int GetX1();					// 左上地圖點座標
		int GetY1();					
		virtual int GetX2();			// 右下地圖點座標
		virtual int GetY2();
		virtual int GetWidth();			// 寬
		virtual int GetHeight();		// 高
		double GetVectorX();			// 拿取方向
		double GetVectorY();
		int GetMoveSpeed();
		int GetShowPriority();			// 拿取顯示優先級
		string GetTag();

		// Setter
		void SetEnable(bool);
		void SetFree(bool);
		void SetDie(bool);
		void SetCollision(bool);
		void SetVector(double, double);
		void SetShowPriority(int);
		virtual void SetXY(int, int);
		void SetSpeed(int);
		void SetHp(int);
		void SetMaxHp(int);
		void SetTag(string);
		
		// member function
		void LoadBitmap(int);
		virtual void LoadBitmap() = 0;
		virtual void OnShow(CGameMap*);						// 在地圖顯示物件
		virtual void OnMove(CGameMap*);
		virtual void OnObjCollision(CGameMap*, CGameObj*) {};
		virtual void OnDie(CGameMap*) {};					// 死亡狀態
		//virtual void OnKeyUp(char);
		//virtual void OnKeyDown(char);
		virtual void Reset();
		virtual void TakeDmg(int);
		double Distance(CGameObj*);
		bool hasObstacle(CGameMap*, CGameObj*);				//	中間有無障礙(概略判斷)
		int CenterX();
		int CenterY();

		// operator
		CGameObj& operator=(const CGameObj& other);

		static vector<CGameObj*> _allObj;
		static void Init()
		{
			_allObj.reserve(256);
			_temp.reserve(256);
		}

		static void AddObj(CGameObj* obj)	// 將物件加入,依優先級插入
		{
			//CGameObjCenter::_allObj.push_back(obj);
			/*CGameObjCenter::_allObj.insert(lower_bound(_allObj.begin(), _allObj.end(), obj,
				[](CGameObj* a, CGameObj* b)
				{
					return a->GetShowPriority() < b->GetShowPriority();
				}
			), obj);*/
			_temp.push_back(obj);
		}

		static void UpdateObjs()
		{
			// 加入物件
			if ((int)CGameObj::_temp.size() > 0)
			{
				for (CGameObj* obj : CGameObj::_temp)
					CGameObj::_allObj.push_back(obj);
				std::sort(CGameObj::_allObj.begin(), CGameObj::_allObj.end(),
					[](CGameObj* a, CGameObj* b)
				{
					return a->GetShowPriority() < b->GetShowPriority();
				});
				CGameObj::_temp.clear();
			}

			// 刪除物件
			for (int i = 0; i < (int)CGameObj::_allObj.size(); i++)
			{
				if (!CGameObj::_allObj.at(i)->IsEnable() && !CGameObj::_allObj.at(i)->IsDie())
				{
					delete CGameObj::_allObj.at(i);
					CGameObj::_allObj.erase(CGameObj::_allObj.begin() + i);
				}
			}
		}

		static void FreeAllObj()
		{
			for (CGameObj* p : _allObj)
			{
				if (p->NeedFree())
				{
					delete p;
				}
			}
			for (CGameObj* p : _temp)
			{
				if (p->NeedFree())
				{
					delete p;
				}
			}
			_temp.clear();
			_allObj.clear();
		}

	protected:
		vector<CAnimation> _animas;						//	動畫清單
		vector<CAnimation>::iterator _animaIter;		//	vector iterator
		int _mx, _my, _moveSpeed;						//	地圖點座標、移動速度
		int _showPriority;								//	顯示優先
		int _hp, _maxHp;								//	血量值、最大血量值
		double _vector[2];								//	移動、方向判別用向量
		double _moveTarget[2];							//	移動位置暫存
		bool _isEnable, _needFree, _isDie, _isCollision;//	是否啟用、釋放、死亡、碰撞
		bool _isLoad;									//	是否已執行 LoadBitmap()
		string _tag;									//	TAG

		virtual void Die();								//	死亡初始化

	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		void copy(const CGameObj&);

		static vector<CGameObj*> _temp;
	};
}

#endif