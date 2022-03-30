#pragma once
#include "CGameObj.h"
namespace game_framework {

	class CEnemy : public CGameObj
	{
	public:
		enum class Anima { INIT_R, INIT_L, RUN_R, RUN_L };
		CEnemy();
		void Initialize();				// ��l��
		void LoadBitmap();				// ���J�ϧ�
		//void OnShow(CGameMap*);					// �N�ϧζK��e��
		void OnMove(CGameMap*);
		void OnObjCollision(CGameObj*);
		//void EnemyOnMove(CGameMap *);

	protected:
		vector<CAnimation>::iterator GetAnima(Anima);
	};
}