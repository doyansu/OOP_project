#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameBullet : public CGameObj
	{
	public:
		CGameBullet();

		void LoadBitmap();
		void OnMove(CGameMap* map);
		//void OnShow(CGameMap* map);

	protected:
		int _damage;		//¤l¼u§ðÀ»¤O

	private:
		void init();
	};

}
