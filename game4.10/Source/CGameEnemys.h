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


	/////////////////////////////////////////////////////////////////////////////
	class CGameEnemy_SNOW_Monkey : public CEnemy
	{
	public:
		static CGameEnemy_SNOW_Monkey& Instance()
		{
			static CGameEnemy_SNOW_Monkey Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}

		CGameEnemy_SNOW_Monkey();
		void LoadBitmap();
		//void OnMove(CGameMap* map);

	protected:

	private:
		//	行動模式
		enum class STATE {
			RANDMOVE,
			MOVETO
		};
		STATE state;
		int _tx, _ty;	//	MOVETO 目標位置
	};
	/////////////////////////////////////////////////////////////////////////////
}
