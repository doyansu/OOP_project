#pragma once
#include "CGameObj.h"
#include "CGameWeapon.h"
#include "CGameObjCenter.h"

namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		enum class Anima {INIT_R, INIT_L, RUN_R, RUN_L, DIE};	//動畫種類
		CCharacter();
		~CCharacter();

		bool IsDoingSomeThing();

		int GetHP();
		int GetMAXHP();
		int GetMP();
		int GetMAXMP();
		int GetShield();
		int GetMAXShield();

		void SetXY(int x, int y);

		void TakeDmg(int);
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);			// 將圖形貼到畫面
		void OnMove(CGameMap*);			// 移動
		void OnDie();
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnKeyUp(char);				
		void OnKeyDown(char);		
		void Reset();					// 重置狀態
		void Init();					// 初始狀態
	
	protected:
		const int _ATTDELAY;						// 近戰攻擊間隔
		int DT;										// direction 朝向控制 1 朝右 0 朝左
		int _mp, _maxMp, _shield, _maxShield;		// 魔力值、最大魔力值、護盾、最大護盾值
		int _damage;								// 近戰傷害
		bool _doSomeThing;								// 射擊判斷
		bool _canAttack;							// 近戰攻擊判斷
		CGameWeapon* _weapons[2];					// 可擁有2把武器
		CGameWeapon** _nowWeapon;								// 當前武器 index

	private:
		int _attCounter;				// 近戰計數器
		int _deathCounter;				// 死亡倒數
		int _shieldCounter;				// 護頓恢復倒數
		void free();
		void ModifyVector(int index, int plus);
		void ModifyShield(int);
		bool hasObstacle(CGameMap*, CGameObj*, CGameObj*);
		vector<CAnimation>::iterator GetAnima(Anima);	// 取得動畫
		
	};
}