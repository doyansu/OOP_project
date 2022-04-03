#ifndef CGAMEOBJ_H
#define CGAMEOBJ_H

#include "CGameMap.h"


namespace game_framework {

	class CGameObj
	{
	public:
		CGameObj();
		CGameObj(const CGameObj& other);
		virtual ~CGameObj();

		// 判斷
		bool Collision(CGameObj*);		// 物件碰撞
		bool Collision(CGameMap*, CGameMap::MapContent = CGameMap::MapContent::WALL);		// 地圖碰撞
		bool IsEnable();				// 是否啟用
		bool NeedFree();				// 是否釋放
		bool IsDie();					// 是否死亡
		bool IsMoveing();

		// Getter
		int GetX1();					// 左上地圖點座標
		int GetY1();					
		virtual int GetX2();			// 右下地圖點座標
		virtual int GetY2();
		double GetVectorX();			// 拿取方向
		double GetVectorY();
		int GetShowPriority();			// 拿取顯示優先級
		string GetTag();

		// Setter
		void SetEnable(bool);
		void SetFree(bool);
		void SetDie(bool);
		void SetVector(double, double);
		void SetMovingDown(bool flag);	
		void SetMovingLeft(bool flag);	
		void SetMovingRight(bool flag); 
		void SetMovingUp(bool flag);	
		void SetShowPriority(int);
		void SetXY(int, int);
		void SetSpeed(int);
		void SetHp(int);
		void SetMaxHp(int);
		void SetTag(string);
		
		// member function
		void LoadBitmap(int);
		virtual void LoadBitmap() {};
		virtual void OnShow(CGameMap*);				// 在地圖顯示物件
		virtual void OnMove(CGameMap*);
		virtual void OnObjCollision(CGameObj*) {};
		virtual void OnDie() {};					// 死亡需做
		virtual void OnKeyUp(char);
		virtual void OnKeyDown(char);
		virtual void Reset();
		virtual void TakeDmg(int);
		double Distance(CGameObj*);
		int CenterX();
		int CenterY();

		// operator
		CGameObj& operator=(const CGameObj& other);

	protected:
		vector<CAnimation> _animas;						//	動畫清單
		vector<CAnimation>::iterator _animaIter;		//	vector iterator
		int _mx, _my, _moveSpeed;						//	地圖點座標、移動速度
		int _showPriority;								//	顯示優先
		int _hp, _maxHp;								//	血量值、最大血量值
		double _vector[2];								//	移動、方向判別用向量
		bool _isEnable, _needFree, _isDie;				//	是否啟用、釋放、死亡
		bool _isMovingDown;								//	是否正在往下移動
		bool _isMovingLeft;								//	是否正在往左移動
		bool _isMovingRight;							//	是否正在往右移動
		bool _isMovingUp;								//	是否正在往上移動
		string _tag;									//	TAG


	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		void copy(const CGameObj&);
	};
}

#endif