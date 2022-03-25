#include "CGameObj.h"
namespace game_framework {

	class CCharacter : public CGameObj
	{
		enum class Anima {INIT_R, INIT_L, RUN_R, RUN_L};
	public:
		CCharacter();
		void LoadBitmap();				// ���J�ϧ�
		void OnShow(CGameMap*);					// �N�ϧζK��e��
		void OnMove(CGameMap *);
		int DT;

	protected:
		int hp;

	private:
		void init();
		vector<CAnimation>::iterator GetAnima(Anima);
		
	};
}