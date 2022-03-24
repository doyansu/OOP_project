#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEnemy.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEnemy: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEnemy::CEnemy()
	{
		Initialize();
	}

	int CEnemy::GetX1()
	{
		return x;
	}

	int CEnemy::GetY1()
	{
		return y;
	}

	int CEnemy::GetX2()
	{
		return x + animation.Width();
	}

	int CEnemy::GetY2()
	{
		return y + animation.Height();
	}

	void CEnemy::Initialize()
	{
		const int X_POS = 10;
		const int Y_POS = 10;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEnemy::LoadBitmap()
	{
		animation.AddBitmap(IDB_enemy0_0, RGB(255, 255, 255));
		animation.AddBitmap(IDB_enemy0_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_enemy0_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_enemy0_3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_enemy0_4, RGB(255, 255, 255));

	}

	void CEnemy::OnMove()
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

	void CEnemy::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEnemy::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEnemy::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEnemy::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEnemy::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEnemy::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}