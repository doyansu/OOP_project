#pragma once
#include "CGameObj.h"
#include "CGameWeapon.h"

namespace game_framework {

	class CEnemy : public CGameObj
	{
	public:
		enum class Anima { INIT_R, INIT_L, RUN_R, RUN_L, DIE};
		CEnemy();
		//CEnemy(const CEnemy&);
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);					// 將圖形貼到畫面
		void OnMove(CGameMap*);
		void OnObjCollision(CGameObj*);
		void OnDie();

		//CEnemy& operator=(const CEnemy&);
	protected:
		CGameWeapon _weapon;
		
	private:
		//void copy(const CEnemy&);
		vector<CAnimation>::iterator GetAnima(Anima);
	};
}