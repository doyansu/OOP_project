#pragma once
#include "CGameBullet.h"

namespace game_framework
{
	class CGamBullet_Init : public CGameBullet
	{
	public:
		CGamBullet_Init();
		
		static CGamBullet_Init& Instance();

		void LoadBitmap();

	private:

	};

}