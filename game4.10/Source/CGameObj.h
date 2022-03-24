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

		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetXY(int, int);
		void SetSpeed(int);
		void Reset();

		virtual void LoadBitmap(int);
		virtual void OnShow(CGameMap*);	// �b�a����ܪ���
		virtual void OnMove();
		virtual void OnKeyUp(char);
		virtual void OnKeyDown(char);

	protected:
		list<CAnimation> _animas;						// list of CAnimation
		list<CAnimation>::iterator _animaIter;			// list iterator
		int _mx, _my, _moveSpeed;						// �a���I�y�СB���ʳt��
		bool _isMovingDown;								// �O�_���b���U����
		bool _isMovingLeft;								// �O�_���b��������
		bool _isMovingRight;							// �O�_���b���k����
		bool _isMovingUp;								// �O�_���b���W����

	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		void init();
	};
}

#endif