#include "CGameObj.h"
namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		CCharacter();
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);					// 將圖形貼到畫面
		void OnMove();

	protected:
		int hp;

	private:
		void init();
	};
}