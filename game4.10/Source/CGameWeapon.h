#pragma once
#include "audio.h"
#include "CGameBullet.h"
#include "CGameArrow.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		enum class Type { INIT, TYPECOUNT };
		enum class Anima { Theta_0, Theta_45, Theta_90, Theta_135, Theta_180, Theta_225, Theta_270, Theta_315, ARROW, ANIMACOUNT};	// �ʵe����

		CGameWeapon(CGameObj* = nullptr);
		~CGameWeapon();
		CGameWeapon(const CGameWeapon&);

		bool CanFire();						// �Z���O�_�i�g��

		void SetTarget(string);
		void SetUser(CGameObj*);
		void SetAttributes(int atk, int cost, int bulletSpeed, int shootDelay);
		void SetCenter(int, int);

		int GetCost();

		void LoadBitmap();
		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);
		//void Shoot(CGameMap*, CGameObj*);	//	�ȮɨS��
		void Shoot(double, double);			//	�Z���g��
		void SetDT(int);					//	�ھڴ¦V���ʵe		
		void OnObjCollision(CGameMap* map, CGameObj* other);

		//CGameWeapon& operator=(const CGameWeapon&);

		static void Init()
		{
			for (int i = 0; i < (int)Type::TYPECOUNT; i++)
			{
				//_Weapons[i] = CGameWeapon();
				_Weapons[i].LoadBitmap();
			}
		}
		static CGameWeapon* CreateObj(int i)
		{
			GAME_ASSERT(i >= 0 && i < (int)Type::TYPECOUNT, "create error");
			return new CGameWeapon(_Weapons[i]);
		}

	protected:
		bool _fire;		
		int _center[2];								//	�ϥΪ̷Q�n����m
		int _cost, _bulletSpeed, _shootDelay;		//	���ӯ�q�B�l�u�t�סB�����t��
		int _fireCounter;							//	�g������p��
		int _DT;									//	�ʵe�P�_
		int _collPlayer;							//	�I�����a�P�w
		CGameBullet* _bullet;						//	�l�u�]�w
		CGameObj* _user;
		AUDIO_ID _shootID;
						
		static CGameWeapon _Weapons[(int)Type::TYPECOUNT];

	private:
		void copy(const CGameWeapon&);
		void free();
		vector<CAnimation>::iterator GetAnima(Anima);	// ���o�ʵe

	};
}
