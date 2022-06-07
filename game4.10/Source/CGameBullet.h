#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameBullet : public CGameObj
	{
	public:
		enum class Type { INIT, HandKnife, enemyNo1, slow, effect_shock, TYPECOUNT};
		CGameBullet();
		//CGameBullet(const CGameBullet& other);

		void AddTarget(string);
		void SetDamage(int);
		void SetSurvive(int);

		virtual void LoadBitmap() = 0;
		virtual void OnMove(CGameMap* map);
		virtual void OnDie(CGameMap*);
		virtual void OnObjCollision(CGameMap*, CGameObj*);

	protected:
		virtual void Die();
		int _damage;		// �l�u�����O
		int _survive;		// �s���ɶ�
		vector<string> _targets;
		Type _bulletType;

	private:
	};

}
