#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CInitialPlayer.h"

namespace game_framework {

	CInitialPlayer::CInitialPlayer()
	{
		Initialize();
	}

	int CInitialPlayer::GetX2()
	{
		return _x + animation.Width();
	}

	int CInitialPlayer::GetY2()
	{
		return _y + animation.Height();
	}

	void CInitialPlayer::Initialize()
	{
		this->Reset();
		const int X_POS = 320;
		const int Y_POS = 200;
		_x = X_POS;
		_y = Y_POS;
	}

	void CInitialPlayer::LoadBitmap()
	{
		animation.AddBitmap(IDB_CH01, RGB(255, 255, 255));
	}

	void CInitialPlayer::OnMove()
	{
		animation.OnMove();
		/*if (_isMovingLeft)
			_x -= _moveSpeed;
		if (_isMovingRight)
			_x += _moveSpeed;
		if (_isMovingUp)
			_y -= _moveSpeed;
		if (_isMovingDown)
			_y += _moveSpeed;*/
		CGameObj::OnMove();
	}

	void CInitialPlayer::OnShow()
	{
		animation.SetTopLeft(_x, _y);
		animation.OnShow();
	}

	void CInitialPlayer::OnKeyUp(char nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_LEFT)
			this->SetMovingLeft(false);
		if (nChar == KEY_RIGHT)
			this->SetMovingRight(false);
		if (nChar == KEY_UP)
			this->SetMovingUp(false);
		if (nChar == KEY_DOWN)
			this->SetMovingDown(false);
	}

	void CInitialPlayer::OnKeyDown(char nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_LEFT)
			this->SetMovingLeft(true);
		if (nChar == KEY_RIGHT)
			this->SetMovingRight(true);
		if (nChar == KEY_UP)
			this->SetMovingUp(true);
		if (nChar == KEY_DOWN)
			this->SetMovingDown(true);
	}
}