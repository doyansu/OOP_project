#ifndef CGAMEOBJ_H
#define CGAMEOBJ_H

#include "CGameMap.h"


namespace game_framework {

	class CGameObj
	{
	public:
		CGameObj();
		CGameObj(const CGameObj& other);

		// �P�_
		bool Collision(CGameObj*);		// ����I��
		bool Collision(CGameMap*);		// �a�ϸI��
		bool IsEnable();				// �O�_�ҥ�
		bool NeedFree();				// �O�_����
		bool IsDie();					// �O�_���`

		// Getter
		int GetX1();					// ���W�a���I�y��
		int GetY1();					
		virtual int GetX2();			// �k�U�a���I�y��
		virtual int GetY2();
		double GetVectorX();				// ������V
		double GetVectorY();
		string GetTag();

		// Setter
		void SetEnable(bool);
		void SetFree(bool);
		void SetDie(bool);
		void SetVector(double, double);
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetXY(int, int);
		void SetSpeed(int);
		void SetTag(string);
		
		// member function
		void LoadBitmap(int);
		virtual void LoadBitmap() {};
		virtual void OnShow(CGameMap*);	// �b�a����ܪ���
		virtual void OnMove(CGameMap*);
		virtual void EnemyOnMove(CGameMap*);
		virtual void OnObjCollision(CGameObj*) {};
		virtual void OnDie() {};
		virtual void OnKeyUp(char);
		virtual void OnKeyDown(char);
		virtual void Reset();
		double Distance(CGameObj*);
		int CenterX();
		int CenterY();

		// operator
		CGameObj& operator=(const CGameObj& other);

	protected:
		vector<CAnimation> _animas;						//	�ʵe�M��
		vector<CAnimation>::iterator _animaIter;		//	vector iterator
		int _mx, _my, _moveSpeed;						//	�a���I�y�СB���ʳt��
		double _vector[2];									//	���ʥΦV�q
		bool _isEnable, _needFree, _isDie;				//	�O�_�ҥΡB����B���`
		bool _isMovingDown;								//	�O�_���b���U����
		bool _isMovingLeft;								//	�O�_���b��������
		bool _isMovingRight;							//	�O�_���b���k����
		bool _isMovingUp;								//	�O�_���b���W����
		string _tag;									//	TAG


	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		void copy(const CGameObj&);
	};
}

#endif