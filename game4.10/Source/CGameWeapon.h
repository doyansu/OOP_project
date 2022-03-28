#pragma once
#include "CGameObj.h"
#include "CGameBullet.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		CGameWeapon();

		bool CanFire();						//	武器是否可射擊

		void LoadBitmap();
		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);
		void Shoot(CGameMap*, CGameObj*);	//	武器射擊

	protected:
		bool _fire;
		int _atk, _cost, _bulletSpeed, _shootGap;		//	攻擊力、消耗能量、子彈速度、攻擊速度
		int _fireCounter;					//	射擊間格計數
		CGameBullet _bullet;				//	子彈設定
		vector<CGameBullet> _bullets;		//	管理子彈 (可能更改)

	private:
		void init();
	};
}
