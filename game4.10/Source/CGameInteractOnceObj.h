#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameInteractOnceObj : public CGameObj
	{
	public:
		enum class Type { REDPOTION, BIGREDPOTION, BULEPOTION, BIGBULEPOTION };
		enum class Anima { MAIN, ARROW, ANIMACOUNT };
		
		CGameInteractOnceObj(Type= Type::REDPOTION);

		int GetX2();
		int GetY2();
		int Width();
		int Height();

		void LoadBitmap();
		void OnObjCollision(CGameMap* map, CGameObj* other);
		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);

	protected:
		int _collPlayer;				//	碰到玩家
		Type _type;						//	類型

		void Die();

	private:
		vector<CAnimation>::iterator GetAnima(Anima type);

	};
}