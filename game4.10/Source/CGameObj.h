#ifndef CGAMEOBJ_H
#define CGAMEOBJ_H

#include "CGameMap.h"


namespace game_framework {

	class CGameObj
	{
	public:
		CGameObj();
		bool Collision(CGameObj*);		// ����I��
		bool Collision(CGameMap*);		// �a�ϸI��
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
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetXY(int, int);
		void SetSpeed(int);
		void SetTag(string);
		
		void LoadBitmap(int);

		virtual void LoadBitmap() {};
		virtual void OnShow(CGameMap*);	// �b�a����ܪ���
		virtual void OnMove(CGameMap*);
		virtual void EnemyOnMove(CGameMap*);
		virtual void OnKeyUp(char);
		virtual void OnKeyDown(char);
		virtual void Reset();

	protected:
		vector<CAnimation> _animas;						// �ʵe�M��
		vector<CAnimation>::iterator _animaIter;		// vector iterator
		int _mx, _my, _moveSpeed;						// �a���I�y�СB���ʳt��
		int _vector[2];									// ���ʥΦV�q
		bool _enable;									// �O�_�ҥ�
		bool _isMovingDown;								// �O�_���b���U����
		bool _isMovingLeft;								// �O�_���b��������
		bool _isMovingRight;							// �O�_���b���k����
		bool _isMovingUp;								// �O�_���b���W����
		string _tag;


	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		void init();
	};
}

#endif