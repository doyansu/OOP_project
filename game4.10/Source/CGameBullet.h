#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameBullet : public CGameObj
	{
	public:
		enum class Type { INIT, TYPECOUNT };
		CGameBullet();
		//CGameBullet(const CGameBullet& other);

		void SetTarget(string);
		void SetDamage(int);

		virtual void LoadBitmap() = 0;
		virtual void OnMove(CGameMap* map);
		virtual void OnObjCollision(CGameMap*, CGameObj*);

	protected:
		int _damage;		//¤l¼u§ðÀ»¤O
		string _target;
		Type _bulletType;

	private:
	};

}
