#pragma once
#include "CGameObj.h"
#include "CGameWeapon.h"

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
		int GetX2();
		int GetY2();
		int GetGold();

		void SetXY(int x, int y);
		void ModifyGold(int);
		void ModifyMp(int);
		void TakeDmg(int);

		void LoadBitmap();				// ���J�ϧ�
		void OnShow(CGameMap*);			// �N�ϧζK��e��
		void OnMove(CGameMap*);			// ����
		void OnDie(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnKeyUp(char);				
		void OnKeyDown(char);		
		void Reset();					// ���m���A
		void Init();					// ��l���A

		static CCharacter* _nowPlayer;
	
	protected:
		const int _ATTDELAY;						// ��ԧ������j
		int _DT;									// direction �¦V���� 1 �¥k 0 �¥�
		int _mp, _maxMp, _shield, _maxShield;		// �]�O�ȡB�̤j�]�O�ȡB�@�ޡB�̤j�@�ޭ�
		int _gold;									// ������
		int _damage;								// ��Զˮ`
		bool _doSomeThing;							// ��L����P�_
		bool _canAttack;							// ��ԧ����P�_
		bool _canInteractive;						// �O�_������i����
		CGameWeapon* _weapons[2];					// �i�֦�2��Z��
		CGameWeapon** _nowWeapon;					// ��e�Z�� index
		int _attCounter;							// ��ԭp�ƾ�
		int _deathCounter;							// ���`�˼�
		int _shieldCounter;							// �@�y��_�˼�

		void ModifyShield(int);
		bool hasObstacle(CGameMap*, CGameObj*, CGameObj*);
		void free();

	private:
		void ModifyVector(int index, int plus);

		vector<CAnimation>::iterator GetAnima(Anima);	// ���o�ʵe
		
	};
}