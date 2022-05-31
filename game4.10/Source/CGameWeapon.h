#pragma once
#include "audio.h"
#include "CGameBullets.h"
#include "CGameArrow.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		enum class Type { INIT, NEWINIT, AK47, TYPECOUNT };
		enum class Anima { Theta_0, Theta_45, Theta_90, Theta_135, Theta_180, Theta_225, Theta_270, Theta_315, ARROW, ANIMACOUNT};	// �ʵe����

		CGameWeapon(CGameObj* = nullptr, Type = Type::INIT);
		~CGameWeapon();
		CGameWeapon(const CGameWeapon&);

		bool CanFire();						// �Z���O�_�i�g��

		void SetTarget(string);
		void SetUser(CGameObj*);
		void SetAttributes(int atk, int cost, int bulletSpeed, int shootDelay);
		void SetCenter(int, int);

		int GetCost();
		Type GetType();

		virtual void LoadBitmap();
		virtual void OnMove(CGameMap* map);
		virtual void OnShow(CGameMap* map);
		virtual void Shoot(double, double);			//	�Z���g��
		void SetDT(int);					//	�ھڴ¦V���ʵe		
		void OnObjCollision(CGameMap* map, CGameObj* other);
		static map<CGameObj*, CGameWeapon*> WeaponMap;

		vector<CAnimation>::iterator GetAnima(Anima);// ���o�ʵe

	protected:
		bool _fire;		
		int _center[2];								//	�ϥΪ̷Q�n����m
		int _cost, _bulletSpeed, _shootDelay;		//	���ӯ�q�B�l�u�t�סB�����t��
		int _atk, _crit, _spread;					//	�l�u�����O�B�z���[���B�����{��
		int _fireCounter;							//	�g������p��
		int _DT;									//	�ʵe�P�_
		int _collPlayer;							//	�I�����a�P�w
		string _target;
		CGameObj* _user;
		AUDIO_ID _shootID;
		Type _weaponType;

		virtual void AddBullet(double x, double y, CGameBullet* newbullet);

	private:
		CGameWeapon& operator=(const CGameWeapon&) {};
		void copy(const CGameWeapon&);
		void free();
		

	};
}
