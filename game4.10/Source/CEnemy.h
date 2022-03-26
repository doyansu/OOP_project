#include "CGameObj.h"
namespace game_framework {

	class CEnemy : public CGameObj
	{
		enum class Anima { INIT_R, INIT_L, RUN_R, RUN_L };
	public:
		CEnemy();
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);					// 將圖形貼到畫面
		void OnMove(CGameMap*);
		//void EnemyOnMove(CGameMap *);

	protected:
		vector<CAnimation>::iterator GetAnima(Anima);
	};
}