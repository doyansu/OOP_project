#pragma once
#include "CGameObj.h"
#include "CGameBullet.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		CGameWeapon();

		bool CanFire();						//	�Z���O�_�i�g��

		void LoadBitmap();
		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);
		void Shoot(CGameMap*, CGameObj*);	//	�Z���g��

	protected:
		bool _fire;
		int _atk, _cost, _bulletSpeed, _shootGap;		//	�����O�B���ӯ�q�B�l�u�t�סB�����t��
		int _fireCounter;					//	�g������p��
		CGameBullet _bullet;				//	�l�u�]�w
		vector<CGameBullet> _bullets;		//	�޲z�l�u (�i����)

	private:
		void init();
	};
}
