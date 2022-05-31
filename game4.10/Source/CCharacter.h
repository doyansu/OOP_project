#pragma once
#include "CGameObj.h"
#include "CGameWeapons.h"
#include "CGameDmgInteger.h"

namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		enum class Anima {INIT_R, INIT_L, RUN_R, RUN_L, DIE, APPEARANCE, ANIMACOUNT};	//動畫種類
		CCharacter();
		~CCharacter();

		bool IsDoingSomeThing();

		int GetHP();
		int GetMAXHP();
		int GetMP();
		int GetMAXMP();
		int GetShield();
		int GetMAXShield();
		int GetX2();
		int GetY2();
		int GetGold();
		CGameWeapon* GetNowWeapon();

		void SetXY(int x, int y);
		void ModifyGold(int);
		void ModifyMp(int);
		void TakeDmg(int);
		void UseSkill();
		void SwitchWeapon();

		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);			// 將圖形貼到畫面
		void OnMove(CGameMap*);			// 移動
		void OnDie(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnKeyUp(char);				
		void OnKeyDown(char);		
		void Reset();					// 重置狀態
		void Init();					// 初始狀態

		static CCharacter* _nowPlayer;
	
	protected:
		const int _SKILLCD, _SKILLTD;				// 技能 CD、技能持續時間
		int _DT;									// direction 朝向控制 1 朝右 0 朝左
		int _mp, _maxMp, _shield, _maxShield;		// 魔力值、最大魔力值、護盾、最大護盾值
		int _gold;									// 金幣數
		int _damage;								// 近戰傷害
		bool _doSomeThing;							// 鍵盤按鍵判斷
		bool _canInteractive;						// 是否有物件可互動
		CGameWeapon* _weapons[2], *_skillWeapon;	// 可擁有2把武器
		int _nowWeapon;								// 當前武器 index
		CGameDmgInteger _dmgInteger;				// 受傷時顯示數字
		CGameDmgInteger _goldInteger, _eneryInteger;// 吃到金幣或能量球顯示數字

		int _deathCounter;							// 死亡倒數
		int _shieldCounter;							// 護頓恢復倒數
		int _skillCounter;							// 技能使用計數

		void ModifyShield(int);
		void free();

	private:
		void ModifyVector(int index, int plus);

		vector<CAnimation>::iterator GetAnima(Anima);	// 取得動畫
		
	};
}