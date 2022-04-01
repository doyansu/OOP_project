#pragma once
#include "CGameObj.h"
#include "CGameBullet.h"


namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		enum class Anima { Right, Left };	// �ʵe����

		CGameWeapon();

		bool CanFire();						// �Z���O�_�i�g��

		void SetUser(CGameObj*);
		void SetAttributes(int atk, int cost, int bulletSpeed, int shootDelay);

		void LoadBitmap();
		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);
		//void Shoot(CGameMap*, CGameObj*);	//	�ȮɨS��
		void Shoot(double, double);			//	�Z���g��
		void SetDT(int);					//	�ھڴ¦V���ʵe					

	protected:
		bool _fire;
		int _atk, _cost, _bulletSpeed, _shootDelay;		//	�����O�B���ӯ�q�B�l�u�t�סB�����t��
		int _fireCounter;					//	�g������p��
		int _DT;							//	�ʵe�P�_
		CGameBullet _bullet;				//	�l�u�]�w
		CGameObj* _user;
						

	private:
		vector<CAnimation>::iterator GetAnima(Anima);	// ���o�ʵe

	};
}
