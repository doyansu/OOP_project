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

	private:

	};

	class CGamBullet_Enemy_No1 : public CGameBullet
	{
	public:
		CGamBullet_Enemy_No1();

		static CGamBullet_Enemy_No1& Instance();

		void LoadBitmap();

	private:

	};

	class CGamBullet_Enemy_Slow : public CGameBullet
	{
	public:
		static CGamBullet_Enemy_Slow& Instance()
		{
			static CGamBullet_Enemy_Slow Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}

		CGamBullet_Enemy_Slow();
		void LoadBitmap();
		void OnMove(CGameMap* map);

	private:
		int survive;		//	存活時間
	};

	class CGamBullet_Effect_shock : public CGameBullet
	{
	public:
		static CGamBullet_Effect_shock& Instance()
		{
			static CGamBullet_Effect_shock Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}

		CGamBullet_Effect_shock();
		void LoadBitmap();
		void OnMove(CGameMap*);

	private:

	};

}