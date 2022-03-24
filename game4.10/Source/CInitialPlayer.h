#include "CGameObj.h"
namespace game_framework {

	class CInitialPlayer : public CGameObj
	{
	public:
		CInitialPlayer();

		void Initialize();				// 設定初始值
		void LoadBitmap();				// 載入圖形

	protected:
		CAnimation animation;		//動畫
	};
}