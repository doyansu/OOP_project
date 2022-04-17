#pragma once
#include "CGameObjCenter.h"
#include "CGameBullet.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		enum class Anima { Right, Left };	// 動畫種類

		CGameWeapon();
		~CGameWeapon();
		CGameWeapon(const CGameWeapon&);

		bool CanFire();						// 武器是否可射擊

		void SetTarget(string);
		void SetAttributes(int atk, int cost, int bulletSpeed, int shootDelay);

		void LoadBitmap();
		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);
		//void Shoot(CGameMap*, CGameObj*);	//	暫時沒用
		void Shoot(double, double);			//	武器射擊
		void SetDT(int);					//	根據朝向更改動畫		

		//CGameWeapon& operator=(const CGameWeapon&);

	protected:
		bool _fire;
		int _cost, _bulletSpeed, _shootDelay;		//	攻擊力、消耗能量、子彈速度、攻擊速度
		int _fireCounter;					//	射擊間格計數
		int _DT;							//	動畫判斷
		CGameBullet* _bullet;				//	子彈設定
						

	private:
		void copy(const CGameWeapon&);
		void free();
		vector<CAnimation>::iterator GetAnima(Anima);	// 取得動畫

	};
}
