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

	int CInitialPlayer::GetX1()
	{
		return x;
	}

	int CInitialPlayer::GetY1()
	{
		return y;
	}

	int CInitialPlayer::GetX2()
	{
		return x + animation.Width();
	}

	int CInitialPlayer::GetY2()
	{
		return y + animation.Height();
	}

	void CInitialPlayer::Initialize()
	{
		const int X_POS = 320;
		const int Y_POS = 200;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CInitialPlayer::LoadBitmap()
	{
		animation.AddBitmap(IDB_ROLE_TEST, RGB(255, 255, 255));
	}

	void CInitialPlayer::OnMove()
	{
		const int STEP_SIZE = 2;
		animation.OnMove();
		if (isMovingLeft)
			x -= STEP_SIZE;
		if (isMovingRight)
			x += STEP_SIZE;
		if (isMovingUp)
			y -= STEP_SIZE;
		if (isMovingDown)
			y += STEP_SIZE;
	}

	void CInitialPlayer::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CInitialPlayer::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CInitialPlayer::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CInitialPlayer::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CInitialPlayer::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CInitialPlayer::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}