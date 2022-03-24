#include "CGameObj.h"
namespace game_framework {

	class CCharacter : public CGameObj
	{
		enum class Anima {INIT, RUN};
	public:
		CCharacter();
		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);					// 將圖形貼到畫面
		void OnMove();

	protected:
		int hp;

	private:
		void init();
		vector<CAnimation>::iterator GetAnima(Anima);
	};
}