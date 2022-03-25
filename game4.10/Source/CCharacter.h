#include "CGameObj.h"
namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		enum class Anima {INIT_R, INIT_L, RUN_R, RUN_L};	//�ʵe����
		CCharacter();
		void LoadBitmap();				// ���J�ϧ�
		void OnShow(CGameMap*);			// �N�ϧζK��e��
		void OnMove(CGameMap*);			// ����
		void Reset();					// ���m���A
	
	protected:
		int DT;
		int _hp;

	private:
		void init();					//��l��
		vector<CAnimation>::iterator GetAnima(Anima);	// ���o�ʵe
		
	};
}