#ifndef CGAMEOBJ_H
#define CGAMEOBJ_H

#include "CGameMap.h"

namespace game_framework {

	class CGameObj
	{
	public:
		CGameObj();
		bool Collision(CGameObj *);
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();

		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int, int);
		void SetSpeed(int);
		void Reset();

		virtual void LoadBitmap(int);
		virtual void OnShow(CGameMap*);	// 在地圖顯示物件
		virtual void OnMove();
		virtual void OnKeyUp(char);
		virtual void OnKeyDown(char);

	protected:
		list<CAnimation> _animas;						// list of CAnimation
		list<CAnimation>::iterator _animaIter;			// list iterator
		int _mx, _my, _moveSpeed;						// 地圖點座標、移動速度
		bool _isMovingDown;								// 是否正在往下移動
		bool _isMovingLeft;								// 是否正在往左移動
		bool _isMovingRight;							// 是否正在往右移動
		bool _isMovingUp;								// 是否正在往上移動

	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		void init();
	};
}

#endif