#include "CGameObj.h"
namespace game_framework {

	class CInitialPlayer : public CGameObj
	{
	public:
		CInitialPlayer();

		int GetX2();
		int GetY2();
		void Initialize();				// 設定初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動
		void OnShow();					// 將圖形貼到畫面

		void OnKeyUp(char);
		void OnKeyDown(char);

	protected:
		CAnimation animation;		//動畫
	};
}