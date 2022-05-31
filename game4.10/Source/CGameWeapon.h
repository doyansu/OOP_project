#pragma once
#include "audio.h"
#include "CGameBullets.h"
#include "CGameArrow.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		enum class Type { INIT, NEWINIT, AK47, TYPECOUNT };
		enum class Anima { Theta_0, Theta_45, Theta_90, Theta_135, Theta_180, Theta_225, Theta_270, Theta_315, ARROW, ANIMACOUNT};	// 動畫種類

		CGameWeapon(CGameObj* = nullptr, Type = Type::INIT);
		~CGameWeapon();
		CGameWeapon(const CGameWeapon&);

		bool CanFire();						// 武器是否可射擊

		void SetTarget(string);
		void SetUser(CGameObj*);
		void SetAttributes(int atk, int cost, int bulletSpeed, int shootDelay);
		void SetCenter(int, int);

		int GetCost();
		Type GetType();

		virtual void LoadBitmap();
		virtual void OnMove(CGameMap* map);
		virtual void OnShow(CGameMap* map);
		virtual void Shoot(double, double);			//	武器射擊
		void SetDT(int);					//	根據朝向更改動畫		
		void OnObjCollision(CGameMap* map, CGameObj* other);
		static map<CGameObj*, CGameWeapon*> WeaponMap;

		vector<CAnimation>::iterator GetAnima(Anima);// 取得動畫

	protected:
		bool _fire;		
		int _center[2];								//	使用者想要的位置
		int _cost, _bulletSpeed, _shootDelay;		//	消耗能量、子彈速度、攻擊速度
		int _atk, _crit, _spread;					//	子彈攻擊力、爆擊加成、散布程度
		int _fireCounter;							//	射擊間格計數
		int _DT;									//	動畫判斷
		int _collPlayer;							//	碰撞玩家判定
		string _target;
		CGameObj* _user;
		AUDIO_ID _shootID;
		Type _weaponType;

		virtual void AddBullet(double x, double y, CGameBullet* newbullet);

	private:
		CGameWeapon& operator=(const CGameWeapon&) {};
		void copy(const CGameWeapon&);
		void free();
		

	};
}
