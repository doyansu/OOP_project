#include "CGameObj.h"
#include "CGameWeapon.h"

namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		enum class Anima {INIT_R, INIT_L, RUN_R, RUN_L};	//�ʵe����
		CCharacter();
		~CCharacter();

		void LoadBitmap();				// ���J�ϧ�
		void OnShow(CGameMap*);			// �N�ϧζK��e��
		void OnMove(CGameMap*);			// ����
		void Shoot();
		void Reset();					// ���m���A

	
	protected:
		int DT;		// ���k�¦V����
		int _hp;
		vector<CGameObj*> _weapon;
		vector<CGameObj*>::iterator _nowWeapon;

	private:
		void init();					//��l��
		void free();
		vector<CAnimation>::iterator GetAnima(Anima);	// ���o�ʵe
		
	};
}