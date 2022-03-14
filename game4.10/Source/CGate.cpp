#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CInitialPlayer.h"
#include "CGate.h"

namespace game_framework {

	CGate::CGate()
	{
		x = y = 0;
	}

	bool CGate::HitPlayer(CInitialPlayer *player)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool CGate::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// 球的左上角x座標
		int y1 = y;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	void CGate::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_GATE1, RGB(0, 0, 0));			// 載入球的圖形
	}

	void CGate::Initialize()
	{
		const int X_POS = 271;
		const int Y_POS = 100;
		x = X_POS;
		y = Y_POS;
	}

	void CGate::OnShow()
	{
		bmp.SetTopLeft(x, y);
		bmp.ShowBitmap();
	}
}