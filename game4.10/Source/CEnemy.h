#include "CGameObj.h"
namespace game_framework {

	class CEnemy : public CGameObj
	{
		enum class Anima { INIT_R, INIT_L, RUN_R, RUN_L };
	public:
		CEnemy();
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnShow(CGameMap*);					// �N�ϧζK��e��
		void OnMove(CGameMap*);
		//void EnemyOnMove(CGameMap *);

	protected:
		vector<CAnimation>::iterator GetAnima(Anima);
	};
}