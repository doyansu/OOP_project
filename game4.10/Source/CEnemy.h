#pragma once
#include "CCharacter.h"
#include "CGameWeapon.h"
#include "CGameTrackObj.h"

namespace game_framework {

	class CEnemy : public CGameObj
	{
	public:
		enum class Anima { RUN_R, RUN_L, DIE};
		CEnemy();
		~CEnemy() override;
		CEnemy(const CEnemy&);
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);					// 將圖形貼到畫面
		void OnMove(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnDie(CGameMap*);

		//CEnemy& operator=(const CEnemy&);
	protected:
		CGameWeapon* _weapon;

		void Die();
		
	private:
		void copy(const CEnemy&);
		void free();
		vector<CAnimation>::iterator GetAnima(Anima);
	};
}