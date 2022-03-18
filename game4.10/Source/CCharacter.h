#include "CGameObj.h"
namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		CCharacter();
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void LoadBitmap();				// 載入圖形
		void OnShow();					// 將擦子圖形貼到畫面

	protected:
		CAnimation animation;		// 擦子的動畫
	};
}