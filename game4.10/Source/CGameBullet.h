#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameBullet : public CGameObj
	{
	public:
		//CGameBullet();
		CGameBullet(int x, int y);
		CGameBullet(const CGameBullet& other);

		void SetTarget(string);
		void SetDamage(int);

		void LoadBitmap();
		void OnMove(CGameMap* map);
		//void OnShow(CGameMap* map);
		void OnObjCollision(CGameMap*, CGameObj*);

	protected:
		int _damage;		//¤l¼u§ðÀ»¤O
		string _target;

	private:
	};

}
