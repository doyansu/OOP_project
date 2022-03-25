#include "CGameObj.h"
namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		enum class Anima {INIT_R, INIT_L, RUN_R, RUN_L};	//動畫種類
		CCharacter();
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);			// 將圖形貼到畫面
		void OnMove(CGameMap*);			// 移動
		void Reset();					// 重置狀態
	
	protected:
		int DT;
		int _hp;

	private:
		void init();					//初始化
		vector<CAnimation>::iterator GetAnima(Anima);	// 取得動畫
		
	};
}