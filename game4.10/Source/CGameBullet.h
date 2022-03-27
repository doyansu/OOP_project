#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameBullet : public CGameObj
	{
	public:
		CGameBullet();
		~CGameBullet();

		void LoadBitmap();
		void OnMove(CGameMap* map);
		//void OnShow(CGameMap* map);

	protected:

	private:
		void init();
	};

}
