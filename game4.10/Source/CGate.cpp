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
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool CGate::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// �y�����W��x�y��
		int y1 = y;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	void CGate::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_GATE1, RGB(0, 0, 0));			// ���J�y���ϧ�
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