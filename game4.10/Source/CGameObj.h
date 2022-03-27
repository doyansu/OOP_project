#ifndef CGAMEOBJ_H
#define CGAMEOBJ_H

#include "CGameMap.h"


namespace game_framework {

	class CGameObj
	{
	public:
		CGameObj();
		bool Collision(CGameObj*);		// 物件碰撞
		bool Collision(CGameMap*);		// 地圖碰撞
		bool IsEnable();

		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		int GetVectorX();
		int GetVectorY();
		string GetTag();

		void SetEnable(bool);
		void SetVector(int, int);
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int, int);
		void SetSpeed(int);
		void SetTag(string);
		
		void LoadBitmap(int);

		virtual void LoadBitmap() {};
		virtual void OnShow(CGameMap*);	// 在地圖顯示物件
		virtual void OnMove(CGameMap*);
		virtual void EnemyOnMove(CGameMap*);
		virtual void OnKeyUp(char);
		virtual void OnKeyDown(char);
		virtual void Reset();

	protected:
		vector<CAnimation> _animas;						// 動畫清單
		vector<CAnimation>::iterator _animaIter;		// vector iterator
		int _mx, _my, _moveSpeed;						// 地圖點座標、移動速度
		int _vector[2];									// 移動用向量
		bool _enable;									// 是否啟用
		bool _isMovingDown;								// 是否正在往下移動
		bool _isMovingLeft;								// 是否正在往左移動
		bool _isMovingRight;							// 是否正在往右移動
		bool _isMovingUp;								// 是否正在往上移動
		string _tag;


	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		void init();
	};
}

#endif