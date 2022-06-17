/*
 * mygame.h: ���ɮ��x�C��������class��interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CGameObj.h"
#include "CGameMap.h"
#include "CCharacter.h"
#include "CEnemy.h"
#include "CGameRoom.h"
#include "CGameTool.h"
#include "CGameFactorys.h"
#include "CGameWeapons.h"
#include "CGameEnemys.h"
#include "CGameTimer.h"

#include "CUIMinMap.h"
#include "CUIButton.h"
#include "CUIWeapon.h"
#include "CUISkill.h"
#include "CUIWeaponSwitch.h"
#include "CUIBossHpBar.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	//	���� audio.h
	/*enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT, 			// 2
		AUDIO_BGM_0
	};*/

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
		void OnMove();
		//void Onclick();
	private:
		// �C�������A
		enum class STATE {
			RUN,				//	���`����
			ABOUT				//	�ഫ about �e��
		};
		STATE gameInitState;

		
		CMovingBitmap background, title, aboutBackGround;			//	�I����

		CAnimation noteboard;										//	�C������
		CAnimation start;											//	�I���}�l�ʵe
		CUIButton btn_newgame, btn_gamenote, btn_about, btn_close;	//	���s

		int btn_posy, btn_movey, board_posy, board_movey;			//	���s�첾

		bool isLoad;	//	�������� OnBeginState() �|�� OnInit() ������ �ΨӧP�_�O�_�w�U�����
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@

	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		// �C�������A
		enum class STATE{ 
			RUN,				//	���`����
			PAUSE,				//	�Ȱ�
			GOTONEXT,			//	���`����
			PLAYERDIE			//	���a���`
		};		
		STATE gameRunState;

		// UI
		CInteger HP, MP, SP, MAXHP, MAXMP, MAXSP, GAMELEVEL, GOLDINTGER;
		CMovingBitmap HPBACKGROUND, SLASH, HPBAR, SPBAR, MPBAR, MINUS, GOLD, pause_UI, setup_UI;
		CUIButton btn_pause, btn_goBack, btn_continue, btn_setup, btn_BGM, btn_soundEffect;
		CUIMinMap minMap;
		int dMinMap;												//	�p�a�Ϧ첾
		int btn_posy, UI_posy, setup_posy;							//	�Ȱ������첾

		// GAMERUN
		CGameMap* gameMap;											//	�a��
		CCharacter* character;										//	����
		CGameRoom* Rooms[MYMAXNOFROOM][MYMAXNOFROOM];				//	�ж�����

		// GOTONEXT
		CAnimation cutscenes;
		int cutscenesCounter;										//	�L���ʵe�p��

		// debug
		CInteger debugx, debugy;

		// function
		void GameEnd();		// �C���������s	
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();

		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@

	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CUIButton btn_statectl;
		CInteger counterDown, enemyDie, coin, SpendTime, gameLevel;
		CMovingBitmap background, colon, minus;
		CAnimation player;

		enum class STATE {start, runAnima, gotoInit };
		STATE state;									// �i�檬�A

		int counter;									// �˼Ƥ��p�ƾ�
		int spendSecond;								// �x�s��O�C���ɶ�
		int animaRate;									// �ʵe�����i��
		const int animaFinishTime;						// �h�[�n�����ʵe

		int endCounter;
	};

	
}