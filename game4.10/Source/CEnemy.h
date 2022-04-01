#pragma once
#include "CGameObj.h"
#include "CGameWeapon.h"

namespace game_framework {

	class CEnemy : public CGameObj
	{
	public:
		enum class Anima { INIT_R, INIT_L, RUN_R, RUN_L, DIE};
		CEnemy();
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);					// 將圖形貼到畫面
		void OnMove(CGameMap*);
		void OnObjCollision(CGameObj*);
		void OnDie();

	protected:
		CGameWeapon _weapon;
		vector<CAnimation>::iterator GetAnima(Anima);
	private:
	};
}