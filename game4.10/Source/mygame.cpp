/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
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
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
	isLoad = false;
}

void CGameStateInit::OnInit()
{
	if (isLoad)
		return;

	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	//logo.LoadBitmap(IDB_BACKGROUND);
	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//

	// Audio
	// BGM
	CAudio::Instance()->Load(AUDIO_BGM_INIT, "sounds\\BGM\\bgm_1Low.wav");
	CAudio::Instance()->Load(AUDIO_BGM_SNOW, "sounds\\BGM\\bgm_5Low.wav"); 
	
	// BTN
	CAudio::Instance()->Load(AUDIO_BTN_DOWN, "sounds\\Btn\\fx_btn1.wav");

	// BOX
	CAudio::Instance()->Load(AUDIO_BOX_OPEN, "sounds\\Box\\fx_chest_open.wav");

	// COIN, ENERGY
	CAudio::Instance()->Load(AUDIO_GET_COIN, "sounds\\Coin\\fx_coin.wav");
	CAudio::Instance()->Load(AUDIO_GET_ENERGY, "sounds\\Coin\\fx_energy.wav");

	// HEALTH
	CAudio::Instance()->Load(AUDIO_HEALTH, "sounds\\Health\\fx_healthpot.wav"); 
	CAudio::Instance()->Load(AUDIO_SHIELDBREAK, "sounds\\Health\\shield_break.wav");
	
	// AUDIO_SWITCH_WEAPON
	CAudio::Instance()->Load(AUDIO_SWITCH_WEAPON, "sounds\\Player\\fx_switch.wav");

	// AUDIO_TRANSFORM
	CAudio::Instance()->Load(AUDIO_TRANSFORM, "sounds\\Player\\fx_transform.wav");

	// WEAPON
	CAudio::Instance()->Load(AUDIO_GUN_0, "sounds\\Shoot\\fx_gun_1.wav");

	//	HIT
	CAudio::Instance()->Load(AUDIO_HIT_ENEMY_0, "sounds\\Hit\\fx_hit.wav");
	CAudio::Instance()->Load(AUDIO_HIT_ENEMY_1, "sounds\\Hit\\fx_hit_p1.wav");
	CAudio::Instance()->Load(AUDIO_HIT_ENEMY_2, "sounds\\Hit\\fx_hit_p2.wav");
	CAudio::Instance()->Load(AUDIO_HIT_ENEMY_3, "sounds\\Hit\\fx_hit_p3.wav");
	CAudio::Instance()->Load(AUDIO_HIT_ENEMY_4, "sounds\\Hit\\fx_hit_p4.wav");
	CAudio::Instance()->Load(AUDIO_HIT_ENEMY_5, "sounds\\Hit\\fx_hit_p5.wav");

	//	DEAD
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_0, "sounds\\Dead\\fx_dead.wav");
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_1, "sounds\\Dead\\fx_dead_cell_absorb.wav");
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_2, "sounds\\Dead\\fx_dead2.wav");
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_3, "sounds\\Dead\\fx_dead3.wav");
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_4, "sounds\\Dead\\fx_dead4.wav");
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_5, "sounds\\Dead\\fx_dead5.wav");
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_6, "sounds\\Dead\\fx_dead6.wav");
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_7, "sounds\\Dead\\fx_dead7.wav");
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_8, "sounds\\Dead\\fx_dead8.wav");
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_9, "sounds\\Dead\\fx_dead_cell_absorb.wav");
	CAudio::Instance()->Load(AUDIO_DEAD_ENEMY_10, "sounds\\Dead\\fx_dead_note.wav");

	//	物件註冊
	Registrar::Registrars();

	//	遊戲物件初始化
	CGameObj::Init();
	CGameRoom::Init();

	// UI
	background.LoadBitmap(IDB_Homepage);
	title.LoadBitmap(IDB_Homepage_title, RGB(0, 0, 0));
	aboutBackGround.LoadBitmap(IDB_aboutBackGround);
	start.AddBitmap(IDB_start0, RGB(0, 0, 0));
	start.AddBitmap(IDB_start1, RGB(0, 0, 0));
	start.AddBitmap(IDB_start2, RGB(0, 0, 0));
	start.AddBitmap(IDB_start3, RGB(0, 0, 0));
	start.AddBitmap(IDB_start4, RGB(0, 0, 0));
	start.AddBitmap(IDB_start5, RGB(0, 0, 0));
	start.AddBitmap(IDB_start6, RGB(0, 0, 0));
	start.AddBitmap(IDB_start7, RGB(0, 0, 0));
	start.AddBitmap(IDB_start6, RGB(0, 0, 0));
	start.AddBitmap(IDB_start5, RGB(0, 0, 0));
	start.AddBitmap(IDB_start4, RGB(0, 0, 0));
	start.AddBitmap(IDB_start3, RGB(0, 0, 0));
	start.AddBitmap(IDB_start2, RGB(0, 0, 0));
	start.AddBitmap(IDB_start1, RGB(0, 0, 0));
	start.SetDelayCount(3);
	btn_newgame.AddBitmap(IDB_newgame0, RGB(0, 0, 0));
	btn_newgame.AddBitmap(IDB_newgame1, RGB(0, 0, 0));
	btn_gamenote.AddBitmap(IDB_gamenote0, RGB(0, 0, 0));
	btn_gamenote.AddBitmap(IDB_gamenote1, RGB(0, 0, 0));
	noteboard.AddBitmap(IDB_note_test, RGB(0, 0, 0));
	btn_about.AddBitmap(IDB_BTN_about_0, RGB(0, 0, 0));
	btn_about.AddBitmap(IDB_BTN_about_1, RGB(0, 0, 0));
	btn_close.AddBitmap(IDB_BTN_close_0, RGB(0, 0, 0));
	btn_close.AddBitmap(IDB_BTN_close_1, RGB(0, 0, 0));

	isLoad = true;
}

void CGameStateInit::OnBeginState()
{
	//	按鈕位置、位移設定
	board_posy = -330;
	board_movey = -20;
	btn_posy = SIZE_Y;
	btn_movey = 10;
	gameInitState = STATE::RUN;

	//	避免未先執行過 OnInit
	this->OnInit();

	//	播放 BGM
	CAudio::Instance()->Play(AUDIO_BGM_INIT);

	//	初始化殺敵數
	CEnemy::ResetDieAmount();

	//	初始化地圖物件關卡數
	CGameMap::Instance()->AddGameLevel(-CGameMap::Instance()->GetGameLevel());

	//	玩家物件初始化
	CCharacter::Instance()->Init();

	//	boss 血條 UI初始化
	CUIBossHpBar::Instance().SetEnable(false);

	//	圖片、動畫、按鈕位置設定
	background.SetTopLeft(0, 0);
	title.SetTopLeft(20, 10);
	start.SetTopLeft((SIZE_X - start.Width()) / 2 - 10, SIZE_Y - start.Height() - 50);
	aboutBackGround.SetTopLeft(0, SIZE_Y);
	btn_about.SetTopLeft(10, SIZE_Y - btn_about.Height() - 20);
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch (gameInitState)
	{
	case game_framework::CGameStateInit::STATE::RUN:
	{
		if (btn_newgame.PointIn(point.x, point.y)) {
			if (!btn_newgame.IsFinalBitmap()) {
				btn_newgame.OnMove();
				CAudio::Instance()->Play(AUDIO_BTN_DOWN);
			}
		}
		else if (btn_gamenote.PointIn(point.x, point.y)) {
			if (!btn_gamenote.IsFinalBitmap()) {
				btn_gamenote.OnMove();
				CAudio::Instance()->Play(AUDIO_BTN_DOWN);
			}
		}
		else if (btn_about.PointIn(point.x, point.y)) {
			if (!btn_about.IsFinalBitmap()) {
				btn_about.OnMove();
				CAudio::Instance()->Play(AUDIO_BTN_DOWN);
			}
		}
		else if (board_movey < 0) {
			btn_movey *= -1;
		}
		break;
	}
	case game_framework::CGameStateInit::STATE::ABOUT:
	{
		if (btn_close.PointIn(point.x, point.y)) {
			if (!btn_close.IsFinalBitmap()) {
				btn_close.OnMove();
				CAudio::Instance()->Play(AUDIO_BTN_DOWN);
			}
		}
		break;	
	}
	default:
		break;
	}
	
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (gameInitState)
	{
	case game_framework::CGameStateInit::STATE::RUN:
	{
		if (btn_newgame.PointIn(point.x, point.y)) {
			Sleep(150);	// 延遲一下再進入遊戲
			//	停止 BGM
			CAudio::Instance()->Stop(AUDIO_BGM_INIT);

			//	開始計時
			CGameTimer::Instance().SetStartPoint(-1);	//	小於 0 起點會被設為當前時間

			GotoGameState(GAME_STATE_RUN);
		}
		else if (btn_gamenote.PointIn(point.x, point.y)) {
			board_movey *= -1;
		}
		else if (btn_about.PointIn(point.x, point.y)) {
			gameInitState = STATE::ABOUT;
		}
		else if (board_movey > 0) {
			board_movey *= -1;
		}
		btn_newgame.Reset();
		btn_gamenote.Reset();
		btn_about.Reset();
		break;
	}
	case game_framework::CGameStateInit::STATE::ABOUT:
	{
		if (btn_close.PointIn(point.x, point.y))
		{
			gameInitState = STATE::RUN;
		}
		btn_close.Reset();
		break;
	}
	default:
		break;
	}
}

void CGameStateInit::OnMove()
{
	start.OnMove();
	btn_posy += btn_movey;
	if (btn_posy > SIZE_Y) {
		btn_posy = SIZE_Y;
	}
	else if (btn_posy < (SIZE_Y - btn_newgame.Height() - 20)) {
		btn_posy = SIZE_Y - btn_newgame.Height() - 20;
	}

	board_posy += board_movey;
	if (board_posy < -noteboard.Height()) {
		board_posy = -noteboard.Height();
	}
	else if (board_posy > (30)) {
		board_posy = 30;
	}

	switch (gameInitState)
	{
	case game_framework::CGameStateInit::STATE::RUN:	//	一般畫面
	{
		if (aboutBackGround.Top() < SIZE_Y)
		{
			aboutBackGround.SetTopLeft(aboutBackGround.Left(), aboutBackGround.Top() + 40);
		}
		else
		{
			aboutBackGround.SetTopLeft(aboutBackGround.Left(), SIZE_Y);
		}
		break;
	}
	case game_framework::CGameStateInit::STATE::ABOUT:	//	進入 about 畫面
	{
		if (aboutBackGround.Top() > 0)
		{
			aboutBackGround.SetTopLeft(aboutBackGround.Left(), aboutBackGround.Top() - 40);
		}
		else
		{
			aboutBackGround.SetTopLeft(aboutBackGround.Left(), 0);
		}
		break;
	}
	default:
		break;
	}
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	/*
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	*/

	//	背景、動畫
	background.ShowBitmap();
	title.ShowBitmap();
	if (btn_posy == SIZE_Y) {
		start.OnShow();
	}
	noteboard.SetTopLeft(110, board_posy);
	noteboard.OnShow();

	//	按鈕
	btn_newgame.SetTopLeft(90, btn_posy);
	btn_newgame.OnShow();
	btn_gamenote.SetTopLeft(120 + btn_newgame.Width(), btn_posy);
	btn_gamenote.OnShow();
	btn_about.OnShow();

	//	about 畫面
	aboutBackGround.ShowBitmap();
	btn_close.SetTopLeft(aboutBackGround.Left() + 472, aboutBackGround.Top() + 120);
	btn_close.OnShow();
	
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g), animaFinishTime(2 * GAME_ONE_SECONED)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
	{
		state = STATE::gotoInit;
	}

	switch (state)
	{
	case game_framework::CGameStateOver::STATE::start:
		if (counter < 6 * GAME_ONE_SECONED)				//	剩 6 秒開始跑動畫
		{
			state = STATE::runAnima;
		}
		break;
	case game_framework::CGameStateOver::STATE::runAnima:
	{
		if(animaRate < animaFinishTime)
			animaRate++;
		else if(!player.IsFinalBitmap() && CGameMap::Instance()->GetGameLevel() != 15)
		{
			player.OnMove();
		}
		break;
	}
	case game_framework::CGameStateOver::STATE::gotoInit:
	{
		animaRate = animaFinishTime;
		if (!player.IsFinalBitmap() && CGameMap::Instance()->GetGameLevel() != 15)
		{
			player.OnMove();
		}
		endCounter--;
		if (counter < 0 || endCounter < 0)
		{
			GotoGameState(GAME_STATE_INIT);
		}
		break;
	}
	default:
		break;
	}
		
}

void CGameStateOver::OnBeginState()
{
	//	設定倒數秒數
	counter = 10 * GAME_ONE_SECONED; // 10 seconds
	//	初始化狀態
	state = STATE::start;
	//	重置動畫進度
	animaRate = 0;
	//	重置動畫
	player.Reset();
	//	設定按兩下的延遲以便看到動畫完成
	endCounter = GAME_ONE_SECONED;
	//	取得計時時間
	spendSecond = CGameTimer::ConvertToSeconds(CGameTimer::Instance().GetTimingTime());
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%

	
	//
	// 開始載入資料
	//

	//	背景
	background.LoadBitmap(IDB_gameover_background);
	background.SetTopLeft(0, 0);

	//	按鈕
	btn_statectl.AddBitmap(IDB_BTN_continue_0, RGB(255, 255, 255));
	btn_statectl.AddBitmap(IDB_BTN_continue_1, RGB(255, 255, 255));
	btn_statectl.SetTopLeft((SIZE_X - btn_statectl.Width()) / 2, SIZE_Y - btn_statectl.Height() - 10);

	//	到計時
	counterDown.SetTopLeft(btn_statectl.Left() + (btn_statectl.Width() / 2) + 20, btn_statectl.Top() + ((btn_statectl.Height() - counterDown.GetHeight()) / 2));
	
	//	殺敵數
	enemyDie.SetTopLeft(390, 245);

	//	取得金幣
	coin.SetColor(CInteger::Color::YELLOW);
	coin.SetTopLeft(240, 245);

	//	冒號
	colon.LoadBitmap(IDB_COLON, RGB(0, 0, 0));

	//	減號
	minus.LoadBitmap(IDB_MINUS, RGB(0, 0, 0));

	//	腳色
	player.AddBitmap(IDB_gameover_player_1, RGB(0, 0, 0));
	player.AddBitmap(IDB_gameover_player_0, RGB(0, 0, 0));


	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnKeyDown(UINT, UINT, UINT)
{
	if (!btn_statectl.IsFinalBitmap()) {
		btn_statectl.OnMove();
		CAudio::Instance()->Play(AUDIO_BTN_DOWN);
	}
}

void CGameStateOver::OnKeyUp(UINT, UINT, UINT)
{
	switch (state)
	{
	case game_framework::CGameStateOver::STATE::start:
		state = STATE::runAnima;
		break;
	case game_framework::CGameStateOver::STATE::runAnima:
		state = STATE::gotoInit;
		break;
	default:
		break;
	}
	btn_statectl.Reset();
}

void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (btn_statectl.PointIn(point.x, point.y)) {
		if (!btn_statectl.IsFinalBitmap()) {
			btn_statectl.OnMove();
			CAudio::Instance()->Play(AUDIO_BTN_DOWN);
		}
	}
}

void CGameStateOver::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (btn_statectl.PointIn(point.x, point.y)) {
		switch (state)
		{
		case game_framework::CGameStateOver::STATE::start:
			state = STATE::runAnima;
			break;
		case game_framework::CGameStateOver::STATE::runAnima:
			state = STATE::gotoInit;
			break;
		default:
			break;
		}
	}
	btn_statectl.Reset();
}

void CGameStateOver::OnShow()
{
	//	背景
	background.ShowBitmap();

	//	按鈕
	btn_statectl.OnShow();

	//	倒數數字
	counterDown.SetInteger(counter / GAME_ONE_SECONED);
	counterDown.ShowBitmap(false);

	//	殺敵數
	enemyDie.SetInteger(CEnemy::GetDieAmount() * animaRate / animaFinishTime);
	enemyDie.ShowBitmap(false);

	//	取得金幣數
	coin.SetInteger(CCharacter::Instance()->GetGold() * animaRate / animaFinishTime);
	coin.ShowBitmap(false);

	//	花費遊戲時間
	int temp;
	temp = spendSecond * animaRate / animaFinishTime;

	SpendTime.SetTopLeft(80, 245);
	SpendTime.SetInteger(temp / 3600);			//	小時
	SpendTime.ShowBitmap(false);
	colon.SetTopLeft(SpendTime.GetLeft() + SpendTime.GetWidth() * SpendTime.GetLen(), 245);
	colon.ShowBitmap();
	SpendTime.SetTopLeft(colon.Left() + colon.Width(), 245);
	SpendTime.SetInteger((temp / 60) % 60);		//	分鐘
	SpendTime.ShowBitmap(false);
	colon.SetTopLeft(SpendTime.GetLeft() + SpendTime.GetWidth() * SpendTime.GetLen(), 245);
	colon.ShowBitmap();
	SpendTime.SetTopLeft(colon.Left() + colon.Width(), 245);
	SpendTime.SetInteger(temp % 60);			//	秒
	SpendTime.ShowBitmap(false);


	//	關卡數
	temp = (1 + CGameMap::Instance()->GetGameLevel()) * animaRate / animaFinishTime;

	if (temp == 16)
		temp--;

	minus.SetTopLeft(15 + 45 * temp, 185);
	minus.ShowBitmap();
	gameLevel.SetTopLeft(minus.Left() - gameLevel.GetWidth(), 185);
	gameLevel.SetInteger(temp < 1 ? 0 : 1 + (temp - 1) / 5);
	gameLevel.ShowBitmap(false);
	gameLevel.SetTopLeft(minus.Left() + minus.Width(), 185);
	gameLevel.SetInteger(temp < 1 ? 0 : 1 + (temp - 1) % 5);
	gameLevel.ShowBitmap(false);

	//	角色
	player.SetTopLeft(15 - (player.Width() / 2) + 45 * temp, 100);
	player.OnShow();
	
	

	
	/*
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(0,0,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "%d S", counter / GAME_ONE_SECONED);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	*/
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g)//, NUMBALLS(28)
{
	
}

CGameStateRun::~CGameStateRun()
{
	//delete [] ball;
	CGameObj::FreeAllObj();
}

void CGameStateRun::OnBeginState()
{
	/*const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;
	for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}
	eraser.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI*/
	

	// 初始化狀態
	gameRunState = STATE::RUN;
	cutscenesCounter = 2 * GAME_ONE_SECONED;

	// UI
	dMinMap = 0;
	btn_setup.Reset();
	//	暫停介面
	btn_posy = -300;
	UI_posy = 0;
	setup_posy = SIZE_Y;
	
	// UI 設定位置
	CUISkill::Instance().SetTopLeft(SIZE_X - CUISkill::Instance().Width() - 20, SIZE_Y - CUISkill::Instance().Height() - 10);
	CUIWeaponSwitch::Instance().SetTopLeft(CUISkill::Instance().Left() + ((CUISkill::Instance().Width() - CUIWeaponSwitch::Instance().Width()) >> 1) - 5, CUISkill::Instance().Top() - CUIWeaponSwitch::Instance().Height() - 10);
	

	// Game
	//	清空地圖物件
	CGameObj::FreeAllObj();
	//	生成地圖
	gameMap->GenerateMap();
	//	將房間資訊傳入小地圖
	minMap.SetRoom(gameMap->GetRooms());
	//	重設角色屬性
	character->Reset();
	character->SetXY(MYMAPWIDTH * gameMap->GetRoom(MYORGROOM, MYORGROOM)->CenterX(),
		MYMAPHIGH * gameMap->GetRoom(MYORGROOM, MYORGROOM)->CenterY());	//	暫時設定初始位置
	CGameObj::AddObj(character);

	//	房間建構
	for (int i = 0; i < MYMAXNOFROOM; i++)
		for (int j = 0; j < MYMAXNOFROOM; j++)
		{
			CGameRoom* room = new CGameRoom(gameMap->GetRoom(i, j));
			room->Initialization(gameMap);
			CGameObj::AddObj(room);
			Rooms[i][j] = room;
		}
	
	// Audio
	CAudio::Instance()->Play(AUDIO_BGM_SNOW, true);

	// TEST
	/*CGameWeapon * w = ProductFactory<CGameWeapon>::Instance().GetProduct((int)CGameWeapon::Type::AK47);
	w->SetXY(MYMAPWIDTH * gameMap->GetRoom(MYORGROOM, MYORGROOM)->CenterX(),
		MYMAPHIGH * gameMap->GetRoom(MYORGROOM, MYORGROOM)->CenterY());
	CGameObj::AddObj(w);*/
	/*CGameTreasure* treasure = CGameTreasure::CreateObj(rand() % (int)CGameTreasure::Type::TYPECOUNT);
	treasure->SetXY(MYMAPWIDTH * gameMap->GetRoom(MYORGROOM, MYORGROOM)->CenterX(),
		MYMAPHIGH * gameMap->GetRoom(MYORGROOM, MYORGROOM)->CenterY());
	CGameObj::AddObj(treasure);*/

}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// 移動背景圖的座標
	//
	/*if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// 移動球
	//
	int i;
	for (i=0; i < NUMBALLS; i++)
		ball[i].OnMove();
	//
	// 移動擦子
	//
	//eraser.OnMove();
	//
	// 判斷擦子是否碰到球
	//
	for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-1);
			//
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	//
	// 移動彈跳的球
	//
	bball.OnMove();*/

	

	// UI button
	if (btn_setup.IsFinalBitmap())
	{
		if (setup_posy > SIZE_Y - setup_UI.Height())
			setup_posy -= 15;
	}
	else
	{
		if (setup_posy < SIZE_Y)
			setup_posy += 15;
	}


	switch (gameRunState)
	{
	case game_framework::CGameStateRun::STATE::PAUSE:		// 暫停處理
	{
		if (UI_posy > -HPBACKGROUND.Height() - 50)
			UI_posy -= 10;
		if (btn_posy < 100)
			btn_posy += 50;
		//	暫停時間不列入計算
		CGameTimer::Instance().SetStartPoint(CGameTimer::Instance().GetStartPoint() + 1);
		break;
	}
		
	case game_framework::CGameStateRun::STATE::GOTONEXT:	//	進下一關
	{
		cutscenesCounter--;
		this->GameEnd();
		cutscenes.OnMove();
		if (cutscenesCounter < 0)
		{
			GotoGameState(GAME_STATE_RUN);
		}
		break;
	}

	case game_framework::CGameStateRun::STATE::PLAYERDIE:	//	玩家死亡
	{
		this->GameEnd();
		GotoGameState(GAME_STATE_OVER);
		break;
	}
		
	case game_framework::CGameStateRun::STATE::RUN:			//	正常執行
	{
		if (btn_posy > -300)
			btn_posy -= 50;

		// 武器 UI 調動
		CUIWeapon::Instance().MoveUI();


		// GAME
		gameMap->OnMove(character->CenterX(), character->CenterY());

		CGameObj::UpdateObjs();

		// 移動、新增物件
		for (int i = 0; i < (int)CGameObj::_allObj.size(); i++)
		{
			CGameObj* obj = CGameObj::_allObj.at(i);
			if (obj->IsEnable())
			{
				obj->OnMove(gameMap);
			}
			else if (obj->IsDie())
			{
				obj->OnDie(gameMap);
			}
		}

		// 處理碰撞
		for (int i = 0; i < (int)CGameObj::_allObj.size(); i++)
		{
			if (!CGameObj::_allObj.at(i)->IsCollision())
				continue;
			for (int j = i + 1; j < (int)CGameObj::_allObj.size(); j++)
				if (CGameObj::_allObj.at(j)->IsCollision() && CGameObj::_allObj.at(i)->Collision(CGameObj::_allObj.at(j)))
				{
					CGameObj::_allObj.at(i)->OnObjCollision(gameMap, CGameObj::_allObj.at(j));
					CGameObj::_allObj.at(j)->OnObjCollision(gameMap, CGameObj::_allObj.at(i));
				}
		}

		//	角色死亡
		if (!character->IsEnable() && !character->IsDie())
		{
			gameRunState = STATE::PLAYERDIE;
		}

		//	UI小地圖
		minMap.OnMove();
		int px = minMap.GetPlayerIn(0), py = minMap.GetPlayerIn(1);
		if (Rooms[px][py]->IsStrat())// 進一般、Boss房間小地圖收起
		{
			if (dMinMap < 180)
				dMinMap += 5;
		}
		else
		{
			if (dMinMap > 0)
				dMinMap -= 5;
		}
		break;
	}
		
	default:
		break;
	}
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//

	// GAME
	gameMap = CGameMap::Instance();
	character = CCharacter::Instance();

	/*int i;
	for (i = 0; i < NUMBALLS; i++)	
		ball[i].LoadBitmap();*/							// 載入第i個球的圖形
	//eraser.LoadBitmap();
	//background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	//Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	/*help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	corner.ShowBitmap(background);							// 將corner貼到background
	bball.LoadBitmap();										// 載入圖形
	hits_left.LoadBitmap();		*/							
	//CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	//CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	//CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//

	
	// UI
	CInteger::LoadBitmap();	// 數字圖片
	HPBACKGROUND.LoadBitmap(IDB_UI_HP);	// bar 背景
	HPBAR.LoadBitmap(IDB_UI_HPBar);		// bar 圖片
	SPBAR.LoadBitmap(IDB_UI_SPBar);
	MPBAR.LoadBitmap(IDB_UI_MPBar);
	SLASH.LoadBitmap(IDB_Slash, RGB(0, 0, 0));	// 斜線圖片
	MINUS.LoadBitmap(IDB_MINUS, RGB(0, 0, 0));	// 減號圖片
	GOLD.LoadBitmap(IDB_gold_0, RGB(255, 255, 255));	//	金幣圖片
	MAXHP.SetTopLeft(82, 7);
	MAXSP.SetTopLeft(82, 28);
	MAXMP.SetTopLeft(82, 48);
	HPBACKGROUND.SetTopLeft(0, 0);

	//	UI小地圖
	minMap.LoadBitmap();


	//	暫停UI
	pause_UI.LoadBitmap(IDB_pause_UI, RGB(255, 255, 255));
	setup_UI.LoadBitmap(IDB_setup_UI, RGB(255, 255, 255));

	//	按鈕
	btn_goBack.AddBitmap(IDB_BTN_goback_0, RGB(255, 255, 255));
	btn_goBack.AddBitmap(IDB_BTN_goback_1, RGB(255, 255, 255));
	btn_continue.AddBitmap(IDB_BTN_continue_0, RGB(255, 255, 255));
	btn_continue.AddBitmap(IDB_BTN_continue_1, RGB(255, 255, 255));
	btn_pause.AddBitmap(IDB_BTN_pause_0, RGB(255, 255, 255));
	btn_pause.AddBitmap(IDB_BTN_pause_1, RGB(255, 255, 255));
	btn_setup.AddBitmap(IDB_BTN_setup_0, RGB(255, 255, 255));
	btn_setup.AddBitmap(IDB_BTN_setup_1, RGB(255, 255, 255));
	btn_BGM.AddBitmap(IDB_BTN_BGM_0, RGB(255, 255, 255));
	btn_BGM.AddBitmap(IDB_BTN_BGM_1, RGB(255, 255, 255));
	btn_soundEffect.AddBitmap(IDB_BTN_soundEffect_0, RGB(255, 255, 255));
	btn_soundEffect.AddBitmap(IDB_BTN_soundEffect_1, RGB(255, 255, 255));

	// 過場動畫
	cutscenes.SetDelayCount(1);
	cutscenes.AddBitmap(IDB_TransferGate_0, RGB(255, 255, 255));
	cutscenes.AddBitmap(IDB_TransferGate_1, RGB(255, 255, 255));
	cutscenes.AddBitmap(IDB_TransferGate_2, RGB(255, 255, 255));
	cutscenes.AddBitmap(IDB_TransferGate_3, RGB(255, 255, 255));
	cutscenes.AddBitmap(IDB_TransferGate_4, RGB(255, 255, 255));
	cutscenes.AddBitmap(IDB_TransferGate_5, RGB(255, 255, 255));
	cutscenes.AddBitmap(IDB_TransferGate_6, RGB(255, 255, 255));
	cutscenes.AddBitmap(IDB_TransferGate_7, RGB(255, 255, 255));
	cutscenes.SetTopLeft((SIZE_X - cutscenes.Width()) / 2, 100);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (gameRunState)
	{
	case game_framework::CGameStateRun::STATE::RUN:
	{
		if (nChar == 0x47)	// 按 G 扣血
			character->TakeDmg(9999);
		else if (nChar == 78)	// 按 N 進入下一關卡
		{
			//test

			gameMap->AddGameLevel(1);
			if (gameMap->GetGameLevel() == 15)//	打完 3-5 通關	
			{
				gameRunState = STATE::PLAYERDIE;
			}
			else
			{
				CAudio::Instance()->Play(AUDIO_TRANSFORM);
				gameRunState = STATE::GOTONEXT;
			}

		}
		else if (nChar == 75)	// 按k殺死關卡小怪
		{
			int px = minMap.GetPlayerIn(0), py = minMap.GetPlayerIn(1);
			if (Rooms[px][py]->IsStrat())
			{
				Rooms[px][py]->kill();
			}
		}


		character->OnKeyDown(nChar);

		// 碰觸傳送門進下一關
		CGameTransferGate* TransferGate = CGameTransferGate::Instance();
		if (character->IsDoingSomeThing() && character->Collision(TransferGate))
		{
			TransferGate->SetDie(false);
			//	關卡數加一
			gameMap->AddGameLevel(1);
			if (gameMap->GetGameLevel() == 15)				//	打完 3-5 通關	
			{
				GotoGameState(GAME_STATE_OVER);
			}
			else
			{
				CAudio::Instance()->Play(AUDIO_TRANSFORM);
				gameRunState = STATE::GOTONEXT;
			}

		}
		break;
	}
	case game_framework::CGameStateRun::STATE::PAUSE:
		break;
	case game_framework::CGameStateRun::STATE::GOTONEXT:
	{
		if (nChar == 78)	// 按 N 跳過動畫
		{
			GotoGameState(GAME_STATE_RUN);
		}
		break;
	}
	default:
		break;
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (gameRunState)
	{
	case game_framework::CGameStateRun::STATE::RUN:
		character->OnKeyUp(nChar);
		break;
	case game_framework::CGameStateRun::STATE::PAUSE:
		break;
	case game_framework::CGameStateRun::STATE::GOTONEXT:
		break;
	case game_framework::CGameStateRun::STATE::PLAYERDIE:
		break;
	default:
		break;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	switch (gameRunState)
	{
	case game_framework::CGameStateRun::STATE::RUN:
	{
		if (btn_pause.PointIn(point.x, point.y)) {
			//	暫停按鈕動畫變換
			if (!btn_pause.IsFinalBitmap()) {
				btn_pause.OnMove();
			}
		}
		else if (CUISkill::Instance().PointIn(point.x, point.y))
		{
			character->UseSkill();
		}
		else if (CUIWeaponSwitch::Instance().PointIn(point.x, point.y))
		{
			character->SwitchWeapon();
		}
		break;
	}
	case game_framework::CGameStateRun::STATE::PAUSE:
	{
		if (btn_goBack.PointIn(point.x, point.y))
		{
			if (!btn_goBack.IsFinalBitmap()) {
				btn_goBack.OnMove();
			}
		}
		else if (btn_continue.PointIn(point.x, point.y))
		{
			if (!btn_continue.IsFinalBitmap()) {
				btn_continue.OnMove();
			}
		}
		break;
	}
		
	case game_framework::CGameStateRun::STATE::GOTONEXT:
		break;
	case game_framework::CGameStateRun::STATE::PLAYERDIE:
		break;
	default:
		break;
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	switch (gameRunState)
	{
	case game_framework::CGameStateRun::STATE::RUN:
	{
		if (btn_pause.PointIn(point.x, point.y)) {
			gameRunState = STATE::PAUSE;
			CAudio::Instance()->Play(AUDIO_BTN_DOWN);
		}
		break;
	}
		
	case game_framework::CGameStateRun::STATE::PAUSE:
	{
		if (btn_goBack.PointIn(point.x, point.y))
		{
			CAudio::Instance()->Play(AUDIO_BTN_DOWN);
			GameEnd();
			GotoGameState(GAME_STATE_INIT);
		}
		else if (btn_continue.PointIn(point.x, point.y))
		{
			CAudio::Instance()->Play(AUDIO_BTN_DOWN);
			gameRunState = STATE::RUN;
			UI_posy = 0;
			btn_setup.Reset();
		}
		else if (btn_setup.PointIn(point.x, point.y))
		{
			CAudio::Instance()->Play(AUDIO_BTN_DOWN);
			btn_setup.OnMove();
		}
		else if (btn_BGM.PointIn(point.x, point.y))
		{
			btn_BGM.OnMove();
			if (!btn_soundEffect.IsFinalBitmap())
				CAudio::Instance()->Play(AUDIO_BTN_DOWN);
			if (btn_BGM.IsFinalBitmap())
			{
				// 暫停所有 BGM
				for (unsigned int id = AUDIO_ID::AUDIO_BGM_INIT; id < AUDIO_ID::AUDIO_BGM_COUNT; id++)
				{
					CAudio::Instance()->Pause(id);
				}
			}
			else
			{
				// 恢復所有 BGM
				for (unsigned int id = AUDIO_ID::AUDIO_BGM_INIT; id < AUDIO_ID::AUDIO_BGM_COUNT; id++)
				{
					CAudio::Instance()->Resume(id);
				}
			}
		}
		else if (btn_soundEffect.PointIn(point.x, point.y))
		{
			btn_soundEffect.OnMove();
			if (btn_soundEffect.IsFinalBitmap())
			{
				CAudio::Instance()->Pause();
			}
			else
			{
				CAudio::Instance()->Resume();
				CAudio::Instance()->Play(AUDIO_BTN_DOWN);
			}

			if (btn_BGM.IsFinalBitmap())
			{
				// 暫停所有 BGM
				for (unsigned int id = AUDIO_ID::AUDIO_BGM_INIT; id < AUDIO_ID::AUDIO_BGM_COUNT; id++)
				{
					CAudio::Instance()->Pause(id);
				}
			}
			else
			{
				// 恢復所有 BGM
				for (unsigned int id = AUDIO_ID::AUDIO_BGM_INIT; id < AUDIO_ID::AUDIO_BGM_COUNT; id++)
				{
					CAudio::Instance()->Resume(id);
				}
			}
		}
		break;
	}
		
	case game_framework::CGameStateRun::STATE::GOTONEXT:
		break;
	case game_framework::CGameStateRun::STATE::PLAYERDIE:
		break;
	default:
		break;
	}

	btn_pause.Reset();
	btn_goBack.Reset();
	btn_continue.Reset();
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	
}

void CGameStateRun::OnShow()
{
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//


	switch (gameRunState)
	{
	case game_framework::CGameStateRun::STATE::PAUSE:
	case game_framework::CGameStateRun::STATE::PLAYERDIE:
	case game_framework::CGameStateRun::STATE::RUN:
	{
		// GAME
		gameMap->OnShow(false);

		for (CGameObj* obj : CGameObj::_allObj)
		{
			if (gameMap->InScreen(obj->GetX1(), obj->GetY1(), obj->GetX2(), obj->GetY2()))
				obj->OnShow(gameMap);
		}

		gameMap->OnShow(true);

		// UI

		HPBACKGROUND.ShowBitmap();
		MAXHP.SetTopLeft(82, 7 + UI_posy);
		MAXSP.SetTopLeft(82, 28 + UI_posy);
		MAXMP.SetTopLeft(82, 48 + UI_posy);
		HPBACKGROUND.SetTopLeft(0, UI_posy);

		// 血量、魔量、護頓 動畫
		int percent = character->GetHP() * 100 / character->GetMAXHP();
		for (int i = 0; i < percent; i++)
		{
			HPBAR.SetTopLeft(27 + i, 10 + UI_posy);
			HPBAR.ShowBitmap();
		}
		percent = character->GetShield() * 100 / character->GetMAXShield();
		for (int i = 0; i < percent; i++)
		{
			SPBAR.SetTopLeft(27 + i, 31 + UI_posy);
			SPBAR.ShowBitmap();
		}
		percent = character->GetMP() * 100 / character->GetMAXMP();
		for (int i = 0; i < percent; i++)
		{
			MPBAR.SetTopLeft(26 + i, 51 + UI_posy);
			MPBAR.ShowBitmap();
		}

		// 血量、魔量、護頓數字
		HP.SetInteger(character->GetHP());
		SP.SetInteger(character->GetShield());
		MP.SetInteger(character->GetMP());
		MAXHP.SetInteger(character->GetMAXHP());
		MAXSP.SetInteger(character->GetMAXShield());
		MAXMP.SetInteger(character->GetMAXMP());
		HP.SetTopLeft(70 - HP.GetLen() * HP.GetWidth(), 7 + UI_posy);
		SP.SetTopLeft(70 - SP.GetLen() * SP.GetWidth(), 28 + UI_posy);
		MP.SetTopLeft(70 - MP.GetLen() * MP.GetWidth(), 48 + UI_posy);
		HP.ShowBitmap(false);
		MP.ShowBitmap(false);
		SP.ShowBitmap(false);
		MAXHP.ShowBitmap(false);
		MAXMP.ShowBitmap(false);
		MAXSP.ShowBitmap(false);

		// 斜線
		SLASH.SetTopLeft(68, 8 + UI_posy);
		SLASH.ShowBitmap();
		SLASH.SetTopLeft(68, 28 + UI_posy);
		SLASH.ShowBitmap();
		SLASH.SetTopLeft(68, 48 + UI_posy);
		SLASH.ShowBitmap();

		//	金幣
		GOLDINTGER.SetInteger(character->GetGold());
		GOLDINTGER.SetTopLeft((SIZE_X - btn_pause.Width() - 50) - GOLDINTGER.GetLen() * GOLDINTGER.GetWidth(), 8 + UI_posy);
		GOLDINTGER.ShowBitmap(false);
		GOLD.SetTopLeft((SIZE_X - btn_pause.Width() - 70) - (GOLDINTGER.GetLen() * GOLDINTGER.GetWidth() + GOLD.Width()), 10 + UI_posy);
		GOLD.ShowBitmap();

		//	關卡數
		GAMELEVEL.SetInteger(1 + gameMap->GetGameLevel() / 5);
		GAMELEVEL.SetTopLeft(SIZE_X - 110 + dMinMap, 200 + btn_pause.Height());
		GAMELEVEL.ShowBitmap(false);
		GAMELEVEL.SetInteger(1 + gameMap->GetGameLevel() % 5);
		GAMELEVEL.SetTopLeft(SIZE_X - 90 + dMinMap, 200 + btn_pause.Height());
		GAMELEVEL.ShowBitmap(false);
		MINUS.SetTopLeft(SIZE_X - 100 + dMinMap, 200 + btn_pause.Height());
		MINUS.ShowBitmap();

		//	UI小地圖
		minMap.SetXY(SIZE_X - 180 + dMinMap, 25 + btn_pause.Height());
		minMap.OnShow();

		//	UI BossHpBar
		CUIBossHpBar::Instance().ShowHpBar();

		//	技能 BOUTTON UI
		CUISkill::Instance().ShowUI();

		//	更換武器 BOUTTON UI
		CUIWeaponSwitch::Instance().SetWeapon(character->GetNowWeapon());
		CUIWeaponSwitch::Instance().ShowUI();

		// 武器 UI 調動
		CUIWeapon::Instance().ShowUI();

		//	暫停介面
		pause_UI.SetTopLeft(((SIZE_X - pause_UI.Width()) >> 1), btn_posy);
		pause_UI.ShowBitmap();
		setup_UI.SetTopLeft((SIZE_X >> 1) - (setup_UI.Width() >> 1), setup_posy);
		setup_UI.ShowBitmap();

		//	按鈕
		btn_pause.SetTopLeft(SIZE_X - btn_pause.Width() - 10, 10 + UI_posy);
		btn_pause.OnShow();
		btn_goBack.SetTopLeft(12 + pause_UI.Left(), btn_posy + 181);
		btn_goBack.OnShow();
		btn_continue.SetTopLeft(8 + btn_goBack.Left() + btn_goBack.Width(), btn_posy + 181);
		btn_continue.OnShow();
		btn_setup.SetTopLeft(8 + btn_continue.Left() + btn_continue.Width(), btn_posy + 181);
		btn_setup.OnShow();
		btn_BGM.SetTopLeft(11 + setup_UI.Left(), 11 + setup_posy);
		btn_BGM.OnShow();
		btn_soundEffect.SetTopLeft(5 + btn_BGM.Left() + btn_BGM.Width(), 11 + setup_posy);
		btn_soundEffect.OnShow();
		break;
	}
	case game_framework::CGameStateRun::STATE::GOTONEXT:
	{
		cutscenes.OnShow();
		break;
	}
	default:
		break;
	}
	
	//debug
	/*debugx.SetTopLeft(0, SIZE_Y - 20);
	debugy.SetTopLeft(80, SIZE_Y - 20);
	debugx.SetInteger(character.GetX1());
	debugy.SetInteger(character.GetY1());
	debugx.ShowBitmap(false);
	debugy.ShowBitmap(false);*/
	/*debugx.SetTopLeft(160, 460);
	debugy.SetTopLeft(240, 460);
	debugx.SetInteger(TransferGate.GetX1());
	debugy.SetInteger(TransferGate.GetY1());
	debugx.ShowBitmap(false);
	debugy.ShowBitmap(false);*/
	/*debugx.SetTopLeft(320, 460);
	debugy.SetTopLeft(400, 460);
	debugx.SetInteger(TransferGate.GetX2());
	debugy.SetInteger(TransferGate.GetY2());
	debugx.ShowBitmap(false);
	debugy.ShowBitmap(false);*/

}

void CGameStateRun::GameEnd()
{
	CAudio::Instance()->Stop(AUDIO_BGM_SNOW);
}
}