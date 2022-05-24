#pragma once
#include "audio.h"
#include "CGameBullet.h"
#include "CGameArrow.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
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

		//CGameWeapon& operator=(const CGameWeapon&);

	protected:
		bool _fire;		
		int _center[2];								//	�ϥΪ̷Q�n����m
		int _cost, _bulletSpeed, _shootDelay;		//	���ӯ�q�B�l�u�t�סB�����t��
		int _fireCounter;							//	�g������p��
		int _DT;									//	�ʵe�P�_
		CGameBullet* _bullet;						//	�l�u�]�w
		CGameObj* _user;
		AUDIO_ID _shootID;
						

	private:
		void copy(const CGameWeapon&);
		void free();
		vector<CAnimation>::iterator GetAnima(Anima);	// ���o�ʵe

	};
}
