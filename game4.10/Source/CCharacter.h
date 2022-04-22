#pragma once
#include "CGameObj.h"
#include "CGameWeapon.h"
#include "CGameObjCenter.h"

namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		enum class Anima {INIT_R, INIT_L, RUN_R, RUN_L, DIE};	//�ʵe����
		CCharacter();
		~CCharacter();

		bool IsDoingSomeThing();

		int GetHP();
		int GetMAXHP();
		int GetMP();
		int GetMAXMP();
		int GetShield();
		int GetMAXShield();

		void SetXY(int x, int y);

		void TakeDmg(int);
		void LoadBitmap();				// ���J�ϧ�
		void OnShow(CGameMap*);			// �N�ϧζK��e��
		void OnMove(CGameMap*);			// ����
		void OnDie();
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnKeyUp(char);				
		void OnKeyDown(char);		
		void Reset();					// ���m���A
		void Init();					// ��l���A
	
	protected:
		const int _ATTDELAY;						// ��ԧ������j
		int DT;										// direction �¦V���� 1 �¥k 0 �¥�
		int _mp, _maxMp, _shield, _maxShield;		// �]�O�ȡB�̤j�]�O�ȡB�@�ޡB�̤j�@�ޭ�
		int _damage;								// ��Զˮ`
		bool _doSomeThing;								// �g���P�_
		bool _canAttack;							// ��ԧ����P�_
		CGameWeapon* _weapons[2];					// �i�֦�2��Z��
		CGameWeapon** _nowWeapon;								// ��e�Z�� index

	private:
		int _attCounter;				// ��ԭp�ƾ�
		int _deathCounter;				// ���`�˼�
		int _shieldCounter;				// �@�y��_�˼�
		void free();
		void ModifyVector(int index, int plus);
		void ModifyShield(int);
		bool hasObstacle(CGameMap*, CGameObj*, CGameObj*);
		vector<CAnimation>::iterator GetAnima(Anima);	// ���o�ʵe
		
	};
}