#include "CGameObj.h"
namespace game_framework {

	class CCharacter : public CGameObj
	{
		enum class Anima {INIT, RUN};
	public:
		CCharacter();
		void LoadBitmap();				// ���J�ϧ�
		void OnShow(CGameMap*);					// �N�ϧζK��e��
		void OnMove();

	protected:
		int hp;

	private:
		void init();
		vector<CAnimation>::iterator GetAnima(Anima);
	};
}