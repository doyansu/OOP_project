#include "CGameObj.h"
namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		CCharacter();
		void LoadBitmap();				// ���J�ϧ�
		void OnShow(CGameMap*);					// �N�ϧζK��e��
		void OnMove();

	protected:
		int hp;

	private:
		void init();
	};
}