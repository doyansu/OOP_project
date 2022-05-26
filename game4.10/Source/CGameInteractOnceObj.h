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

		int GetX2();
		int GetY2();
		int Width();
		int Height();

		void LoadBitmap();
		void OnObjCollision(CGameMap* map, CGameObj* other);
		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);

		
		static CGameInteractOnceObj* CreateObj(int i)
		{
			static CGameInteractOnceObj _interactOnceObjs[(int)Type::TYPECOUNT];
			static bool isLoad = false;
			if(isLoad == false)
			{
				for (int i = 0; i < (int)Type::TYPECOUNT; i++)
				{
					_interactOnceObjs[i] = CGameInteractOnceObj((CGameInteractOnceObj::Type)i);
					_interactOnceObjs[i].LoadBitmap();
				}
				isLoad = true;
			}
			
			GAME_ASSERT(i >= 0 && i < (int)Type::TYPECOUNT, "create error");
			return new CGameInteractOnceObj(_interactOnceObjs[i]);
		}

	protected:
		int _collPlayer;				//	碰到玩家
		Type _type;						//	類型

		void Die();

		

	private:
		CGameInteractOnceObj(Type = Type::REDPOTION);
		vector<CAnimation>::iterator GetAnima(Anima type);

	};
}