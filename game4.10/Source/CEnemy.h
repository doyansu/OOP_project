#pragma once
#include "CGameWeapons.h"
#include "CAnimationEnemyAppear.h"
#include "CGameDmgInteger.h"

namespace game_framework {

	class CEnemy : public CGameObj
	{
	public:
		enum class Type { INIT, SNOW_SLOW, TYPECOUNT };
		enum class Anima { RUN_R, RUN_L, DIE, APPEARANCE, ANIMACOUNT};
		CEnemy();
		~CEnemy() override;
		CEnemy(const CEnemy&);

		bool hasAppeared();
		Type GetType();

		void TakeDmg(int);
		void LoadBitmap();				// ���J�ϧ�
		void OnShow(CGameMap*);					// �N�ϧζK��e��
		void OnMove(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnDie(CGameMap*);

		static int GetDieAmount()
		{
			return _amountDie;
		}

		static void ResetDieAmount()
		{
			_amountDie = 0;
		}

		//CEnemy& operator=(const CEnemy&);
	protected:
		CGameWeapon* _weapon;
		Type _enemyType;
		CGameDmgInteger _dmgInteger;

		void Die();
		vector<CAnimation>::iterator GetAnima(Anima);

		static int _amountDie;
		

	private:
		void copy(const CEnemy&);
		void free();
		
	};
}