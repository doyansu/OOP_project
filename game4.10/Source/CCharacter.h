#include "CGameObj.h"
namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		CCharacter();
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void LoadBitmap();				// ���J�ϧ�
		void OnShow();					// �N���l�ϧζK��e��

	protected:
		CAnimation animation;		// ���l���ʵe
	};
}