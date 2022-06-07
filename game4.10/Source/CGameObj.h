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

		// �P�_
		bool Collision(CGameObj*);		// ����I��
		bool Collision(CGameMap*, CGameMap::ContentType = CGameMap::ContentType::WALL);		// �a�ϸI��
		bool IsEnable();				// �O�_�ҥ�
		bool NeedFree();				// �O�_����
		bool IsDie();					// �O�_���`
		bool IsCollision();				// �O�_�ҥθI��
		bool IsLoad();					// �O�_�w���� LoadBitmap()

		// Getter
		int GetX1();					// ���W�a���I�y��
		int GetY1();					
		virtual int GetX2();			// �k�U�a���I�y��
		virtual int GetY2();
		virtual int GetWidth();			// �e
		virtual int GetHeight();		// ��
		double GetVectorX();			// ������V
		double GetVectorY();
		int GetMoveSpeed();
		int GetShowPriority();			// ��������u����
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
		virtual void OnShow(CGameMap*);						// �b�a����ܪ���
		virtual void OnMove(CGameMap*);
		virtual void OnObjCollision(CGameMap*, CGameObj*) {};
		virtual void OnDie(CGameMap*) {};					// ���`���A
		//virtual void OnKeyUp(char);
		//virtual void OnKeyDown(char);
		virtual void Reset();
		virtual void TakeDmg(int);
		double Distance(CGameObj*);
		bool hasObstacle(CGameMap*, CGameObj*);				//	�������L��ê(�����P�_)
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

		static void AddObj(CGameObj* obj)	// �N����[�J,���u���Ŵ��J
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
			// �[�J����
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

			// �R������
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
		vector<CAnimation> _animas;						//	�ʵe�M��
		vector<CAnimation>::iterator _animaIter;		//	vector iterator
		int _mx, _my, _moveSpeed;						//	�a���I�y�СB���ʳt��
		int _showPriority;								//	����u��
		int _hp, _maxHp;								//	��q�ȡB�̤j��q��
		double _vector[2];								//	���ʡB��V�P�O�ΦV�q
		double _moveTarget[2];							//	���ʦ�m�Ȧs
		bool _isEnable, _needFree, _isDie, _isCollision;//	�O�_�ҥΡB����B���`�B�I��
		bool _isLoad;									//	�O�_�w���� LoadBitmap()
		string _tag;									//	TAG

		virtual void Die();								//	���`��l��

	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		void copy(const CGameObj&);

		static vector<CGameObj*> _temp;
	};
}

#endif