#pragma once
#include "CCharacter.h"
#include "CGameWeapons.h"
#include "CGameTrackObj.h"
#include "CAnimationEnemyAppear.h"

namespace game_framework {

	class CEnemy : public CGameObj
	{
	public:
		enum class Type { INIT, TYPECOUNT };
		enum class Anima { RUN_R, RUN_L, DIE, APPEARANCE, ANIMACOUNT};
		CEnemy();
		~CEnemy() override;
		CEnemy(const CEnemy&);

		bool hasAppeared();
		Type GetType();

		void TakeDmg(int);
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);					// 將圖形貼到畫面
		void OnMove(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnDie(CGameMap*);

		//CEnemy& operator=(const CEnemy&);
	protected:
		CGameWeapon* _weapon;
		Type _enemyType;

		void Die();
		vector<CAnimation>::iterator GetAnima(Anima);

	private:
		void copy(const CEnemy&);
		void free();
		
	};
}