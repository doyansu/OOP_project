#include "CGameObj.h"
namespace game_framework {

	class CInitialPlayer : public CGameObj
	{
	public:
		CInitialPlayer();

		int GetX2();
		int GetY2();
		void Initialize();				// �]�w��l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// ����
		void OnShow();					// �N�ϧζK��e��

		void OnKeyUp(char);
		void OnKeyDown(char);

	protected:
		CAnimation animation;		//�ʵe
	};
}