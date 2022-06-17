/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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

	//	移到 audio.h
	/*enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT, 			// 2
		AUDIO_BGM_0
	};*/

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
		void OnMove();
		//void Onclick();
	private:
		// 遊戲內狀態
		enum class STATE {
			RUN,				//	正常執行
			ABOUT				//	轉換 about 畫面
		};
		STATE gameInitState;

		
		CMovingBitmap background, title, aboutBackGround;			//	背景圖

		CAnimation noteboard;										//	遊戲說明
		CAnimation start;											//	點擊開始動畫
		CUIButton btn_newgame, btn_gamenote, btn_about, btn_close;	//	按鈕

		int btn_posy, btn_movey, board_posy, board_movey;			//	按鈕位移

		bool isLoad;	//	不知為何 OnBeginState() 會比 OnInit() 先執行 用來判斷是否已下載資料
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作

	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		// 遊戲內狀態
		enum class STATE{ 
			RUN,				//	正常執行
			PAUSE,				//	暫停
			GOTONEXT,			//	正常執行
			PLAYERDIE			//	玩家死亡
		};		
		STATE gameRunState;

		// UI
		CInteger HP, MP, SP, MAXHP, MAXMP, MAXSP, GAMELEVEL, GOLDINTGER;
		CMovingBitmap HPBACKGROUND, SLASH, HPBAR, SPBAR, MPBAR, MINUS, GOLD, pause_UI, setup_UI;
		CUIButton btn_pause, btn_goBack, btn_continue, btn_setup, btn_BGM, btn_soundEffect;
		CUIMinMap minMap;
		int dMinMap;												//	小地圖位移
		int btn_posy, UI_posy, setup_posy;							//	暫停介面位移

		// GAMERUN
		CGameMap* gameMap;											//	地圖
		CCharacter* character;										//	角色
		CGameRoom* Rooms[MYMAXNOFROOM][MYMAXNOFROOM];				//	房間物件

		// GOTONEXT
		CAnimation cutscenes;
		int cutscenesCounter;										//	過場動畫計數

		// debug
		CInteger debugx, debugy;

		// function
		void GameEnd();		// 遊戲結束重製	
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();

		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作

	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CUIButton btn_statectl;
		CInteger counterDown, enemyDie, coin, SpendTime, gameLevel;
		CMovingBitmap background, colon, minus;
		CAnimation player;

		enum class STATE {start, runAnima, gotoInit };
		STATE state;									// 進行狀態

		int counter;									// 倒數之計數器
		int spendSecond;								// 儲存花費遊戲時間
		int animaRate;									// 動畫完成進度
		const int animaFinishTime;						// 多久要完成動畫

		int endCounter;
	};

	
}