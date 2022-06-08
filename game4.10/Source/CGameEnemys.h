#pragma once
#include "CEnemy.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//	狙擊兵
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
	//	霰彈兵
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
	//	小雪猿
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
		void OnMove(CGameMap* map);

	protected:

	private:
		//	行動模式
		enum class STATE {
			RANDMOVE,
			MOVETO
		};
		STATE state;
		int _tx, _ty;			//	MOVETO 目標位置
		int _maxTrackTime;
	};
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	水晶礦
	class CGameEnemy_Crystal : public CEnemy
	{
	public:
		static CGameEnemy_Crystal& Instance()
		{
			static CGameEnemy_Crystal Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}

		CGameEnemy_Crystal();
		void LoadBitmap();
		void OnMove(CGameMap* map);

	protected:
		void Die();

	private:
	};
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	金礦
	class CGameEnemy_Gold : public CEnemy
	{
	public:
		static CGameEnemy_Gold& Instance()
		{
			static CGameEnemy_Gold Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}

		CGameEnemy_Gold();
		void LoadBitmap();
		void OnMove(CGameMap* map);

	protected:
		void Die();

	private:
	};
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	水晶巨蟹
	class CGameEnemy_SNOW_BOSS_0 : public CEnemy
	{
	public:
		static CGameEnemy_SNOW_BOSS_0& Instance()
		{
			static CGameEnemy_SNOW_BOSS_0 Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}

		CGameEnemy_SNOW_BOSS_0();
		void LoadBitmap();
		void OnMove(CGameMap* map);
		void OnObjCollision(CGameMap* map, CGameObj* other);
		void TakeDmg(int);

	protected:
		
	private:
		//	行動模式
		enum class STATE {
			MOVE,
			ATTACK,
			DEFENSE
		};
		STATE state;

		int _changeModeCounter;
		int _defenseCounter;
	};
	/////////////////////////////////////////////////////////////////////////////

	
}
