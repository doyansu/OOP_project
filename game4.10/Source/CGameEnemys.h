#pragma once
#include "CEnemy.h"

namespace game_framework
{
	class CGameEnemy_Init : public CEnemy
	{
	public:
		static CGameEnemy_Init& Instance()
		{
			static CGameEnemy_Init Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}

		CGameEnemy_Init();
		void LoadBitmap();
	protected:

	private:

	};
}
