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


	void CInitialPlayer::Initialize()
	{
		this->Reset();
		const int X_POS = 320;
		const int Y_POS = 200;
		_mx = X_POS;
		_my = Y_POS;
	}

	void CInitialPlayer::LoadBitmap()
	{
		_animaIter->AddBitmap(IDB_CH1_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_3, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_CH1_2, RGB(255, 255, 255));
		_animaIter->SetDelayCount(5);
	}

}