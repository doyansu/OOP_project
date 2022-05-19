#pragma once
#include "CGameObj.h"
#include "CGameArrow.h"

namespace game_framework
{
	class CGameInteractOnceObj : public CGameObj
	{
	public:
		enum class Type { REDPOTION, BIGREDPOTION, BULEPOTION, BIGBULEPOTION, TYPECOUNT };
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

		
		static void Init()
		{
			for (int i = 0; i < (int)Type::TYPECOUNT; i++)
			{
				_interactOnceObjs[i] = CGameInteractOnceObj((CGameInteractOnceObj::Type)i);
				_interactOnceObjs[i].LoadBitmap();
			}
		}
		static CGameInteractOnceObj* CreateObj(int i)
		{
			GAME_ASSERT(i >= 0 && i < (int)Type::TYPECOUNT, "create error");
			return new CGameInteractOnceObj(_interactOnceObjs[i]);
		}

	protected:
		int _collPlayer;				//	碰到玩家
		Type _type;						//	類型

		void Die();

		static CGameInteractOnceObj _interactOnceObjs[(int)Type::TYPECOUNT];

	private:
		vector<CAnimation>::iterator GetAnima(Anima type);

	};
}