#pragma once
#include "CEnemy.h"

namespace game_framework
{
	class CGameEnemy_Init : public CEnemy
	{
	public:
		static CGameEnemy_Init& Instance();

		CGameEnemy_Init();
		void LoadBitmap();
	protected:

	private:

	};
}
