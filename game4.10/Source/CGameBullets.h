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

	class CGamBullet_HandKnife : public CGameBullet
	{
	public:
		CGamBullet_HandKnife();

		static CGamBullet_HandKnife& Instance();

		void LoadBitmap();
		void OnMove(CGameMap*);
		void OnDie(CGameMap*);

	private:

	};

}