#pragma once
#include "CGameObj.h"
#include "CGameWeapon.h"
#include "CGameObjCenter.h"

namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		enum class Anima {INIT_R, INIT_L, RUN_R, RUN_L};	//動畫種類
		CCharacter();

		void TakeDmg(int);
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);			// 將圖形貼到畫面
		void OnMove(CGameMap*);			// 移動
		void OnDie();
		void OnKeyUp(char);				
		void OnKeyDown(char);		
		void Reset();					// 重置狀態

	
	protected:
		const int _ATTDELAY;
		int DT;										// direction 朝向控制 1 朝右 0 朝左
		int _mp, _maxMp, _shield, _maxShield;		// 魔力值、最大魔力值、護盾、最大護盾值
		int _damage;								// 近戰傷害
		bool _doFire;								// 射擊判斷
		bool _canAttack;							// 近戰攻擊判斷
		vector<CGameWeapon> _weapon;				// 可擁有2把武器
		vector<CGameWeapon>::iterator _nowWeapon;	// 當前武器

	private:
		int _attCounter;				// 近戰計數器
		void init();					// 初始化
		void free();
		void ModifyVector(int index, int plus);
		vector<CAnimation>::iterator GetAnima(Anima);	// 取得動畫
		
	};
}