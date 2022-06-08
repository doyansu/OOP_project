#pragma once
#include "CEnemy.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//	�����L
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
	//	�żu�L
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
	//	�p����
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
		//	��ʼҦ�
		enum class STATE {
			RANDMOVE,
			MOVETO
		};
		STATE state;
		int _tx, _ty;			//	MOVETO �ؼЦ�m
		int _maxTrackTime;
	};
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	�����q
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
	//	���q
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
	//	��������
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
		//	��ʼҦ�
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
