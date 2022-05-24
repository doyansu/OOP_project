#pragma once
#include "audio.h"
#include "CGameBullet.h"
#include "CGameArrow.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		enum class Anima { Theta_0, Theta_45, Theta_90, Theta_135, Theta_180, Theta_225, Theta_270, Theta_315, ARROW, ANIMACOUNT};	// 動畫種類

		CGameWeapon(CGameObj* = nullptr);
		~CGameWeapon();
		CGameWeapon(const CGameWeapon&);

		bool CanFire();						// 武器是否可射擊

		void SetTarget(string);
		void SetUser(CGameObj*);
		void SetAttributes(int atk, int cost, int bulletSpeed, int shootDelay);
		void SetCenter(int, int);

		int GetCost();

		void LoadBitmap();
		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);
		//void Shoot(CGameMap*, CGameObj*);	//	暫時沒用
		void Shoot(double, double);			//	武器射擊
		void SetDT(int);					//	根據朝向更改動畫		

		//CGameWeapon& operator=(const CGameWeapon&);

	protected:
		bool _fire;		
		int _center[2];								//	使用者想要的位置
		int _cost, _bulletSpeed, _shootDelay;		//	消耗能量、子彈速度、攻擊速度
		int _fireCounter;							//	射擊間格計數
		int _DT;									//	動畫判斷
		CGameBullet* _bullet;						//	子彈設定
		CGameObj* _user;
		AUDIO_ID _shootID;
						

	private:
		void copy(const CGameWeapon&);
		void free();
		vector<CAnimation>::iterator GetAnima(Anima);	// 取得動畫

	};
}
