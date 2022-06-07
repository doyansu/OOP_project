#pragma once
#include "CGameObj.h"
#include "CGameWeapons.h"
#include "CGameDmgInteger.h"

namespace game_framework {

	class CCharacter : public CGameObj
	{
	public:
		enum class Anima {INIT_R, INIT_L, RUN_R, RUN_L, DIE, APPEARANCE, ANIMACOUNT};	//�ʵe����
		CCharacter();
		~CCharacter();

		bool IsDoingSomeThing();
		bool IsMoveing();				// �O�_���b����

		int GetHP();
		int GetMAXHP();
		int GetMP();
		int GetMAXMP();
		int GetShield();
		int GetMAXShield();
		int GetX2();
		int GetY2();
		int GetGold();
		CGameWeapon* GetNowWeapon();

		void SetXY(int x, int y);
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void ModifyGold(int);
		void ModifyMp(int);
		void TakeDmg(int);
		void UseSkill();
		void SwitchWeapon();

		void LoadBitmap();				// ���J�ϧ�
		void OnShow(CGameMap*);			// �N�ϧζK��e��
		void OnMove(CGameMap*);			// ����
		void OnDie(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnKeyUp(char);				
		void OnKeyDown(char);		
		void Reset();					// ���m���A
		void Init();					// ��l���A

		static CCharacter* Instance()
		{
			static CCharacter instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				instance.LoadBitmap();
				isLoad = true;
			}
			return &instance;
		}
	
	protected:
		const int _SKILLCD, _SKILLTD;				// �ޯ� CD�B�ޯ����ɶ�
		int _DT;									// direction �¦V���� 1 �¥k 0 �¥�
		int _mp, _maxMp, _shield, _maxShield;		// �]�O�ȡB�̤j�]�O�ȡB�@�ޡB�̤j�@�ޭ�
		int _gold;									// ������
		bool _doSomeThing;							// ��L����P�_
		bool _doHandKnife;							// ��M����
		bool _canInteractive;						// �O�_������i����
		bool _isMovingDown;							// �O�_���b���U����
		bool _isMovingLeft;							// �O�_���b��������
		bool _isMovingRight;						// �O�_���b���k����
		bool _isMovingUp;							// �O�_���b���W����
		CGameWeapon* _weapons[2], *_skillWeapon;	// �i�֦�2��Z��
		int _nowWeapon;								// ��e�Z�� index
		CGameDmgInteger _dmgInteger;				// ���ˮ���ܼƦr
		CGameDmgInteger _goldInteger, _eneryInteger;// �Y������ί�q�y��ܼƦr

		int _deathCounter;							// ���`�˼�
		int _shieldCounter;							// �@�y��_�˼�
		int _skillCounter;							// �ޯ�ϥέp��
		int _hitCounter;							// ���˫�u�ȵL�Ī��p��

		void ModifyShield(int);
		void free();

	private:
		void ModifyVector(int index, int plus);

		vector<CAnimation>::iterator GetAnima(Anima);	// ���o�ʵe
		
	};
}