#pragma once
#include "CEnemy.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	class CGameEnemy_Init : public CEnemy
	{
	public:
		static CGameEnemy_Init& Instance();

		CGameEnemy_Init();
		void LoadBitmap();
	protected:

	private:

	};

	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	class CGameEnemy_SNOW_0 : public CEnemy
	{
	public:
		static CGameEnemy_SNOW_0& Instance()
		{
			static CGameEnemy_SNOW_0 Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}
		
		CGameEnemy_SNOW_0();
		void LoadBitmap();
	protected:

	private:

	};
	/////////////////////////////////////////////////////////////////////////////
}
