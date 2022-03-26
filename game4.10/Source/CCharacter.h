#include "CGameObj.h"
#include "CGameWeapon.h"

namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		enum class Anima {INIT_R, INIT_L, RUN_R, RUN_L};	//動畫種類
		CCharacter();
		~CCharacter();

		void LoadBitmap();				// 載入圖形
		void OnShow(CGameMap*);			// 將圖形貼到畫面
		void OnMove(CGameMap*);			// 移動
		void OnKeyUp(char);				
		void OnKeyDown(char);		
		void ModifyVector(int index, int plus);
		void Shoot();
		void Reset();					// 重置狀態

	
	protected:
		int DT;		// 朝向控制
		int _hp;
		vector<CGameWeapon> _weapon;
		vector<CGameWeapon>::iterator _nowWeapon;

	private:
		void init();					//初始化
		void free();
		vector<CAnimation>::iterator GetAnima(Anima);	// 取得動畫
		
	};
}