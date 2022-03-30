#pragma once
#include "CGameObj.h"
#include "CGameBullet.h"
#include "CGameObjCenter.h"
#include "CEnemy.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		enum class Anima { Right, Left };	//�ʵe����

		CGameWeapon();

		bool CanFire();						//	�Z���O�_�i�g��

		void LoadBitmap();
		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);
		void Shoot(CGameMap*, CGameObj*);	//	�Z���g��
		void DT_D(int dt);					//	�ھڴ¦V���ʵe

	protected:
		bool _fire;
		int _atk, _cost, _bulletSpeed, _shootGap;		//	�����O�B���ӯ�q�B�l�u�t�סB�����t��
		int _fireCounter;					//	�g������p��
		CGameBullet _bullet;				//	�l�u�]�w
		CEnemy test;
		vector<CGameBullet> _bullets;		//	�޲z�l�u (�i����)

	private:
		void init();
		vector<CAnimation>::iterator GetAnima(Anima);	// ���o�ʵe

	};
}
