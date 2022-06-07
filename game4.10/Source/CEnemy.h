#pragma once
#include "CGameWeapons.h"
#include "CAnimationEnemyAppear.h"
#include "CGameDmgInteger.h"

namespace game_framework {

	class CEnemy : public CGameObj
	{
	public:
		//	一般敵人、BOSS、特殊敵人物件
		enum class Type { INIT, SNOW_SLOW, SNOW_Monkey_0, TYPECOUNT, BOSS_SNOW_0, BOSSEND, crystal, gold, END};
		enum class Anima { RUN_R, RUN_L, DIE, APPEARANCE, ANIMACOUNT};
		CEnemy();
		~CEnemy() override;
		CEnemy(const CEnemy&);

		bool hasAppeared();
		Type GetType();
		int GetX2();
		int GetY2();

		void TakeDmg(int);
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);					// 將圖形貼到畫面
		void OnMove(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnDie(CGameMap*);

		static int GetDieAmount()
		{
			return _amountDie;
		}

		static void ResetDieAmount()
		{
			_amountDie = 0;
		}

		//CEnemy& operator=(const CEnemy&);
	protected:
		CGameWeapon* _weapon;				// 可配戴武器
		Type _enemyType;					// 怪物類型
		CGameDmgInteger _dmgInteger;		// 受傷數字
		int _maxSearch;						// 最大搜索範圍

		void Die();
		vector<CAnimation>::iterator GetAnima(Anima);

		static int _amountDie;
		

	private:
		void copy(const CEnemy&);
		void free();
		
	};
}