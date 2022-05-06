#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CUIMinMap.h"

namespace game_framework
{
	CUIMinMap::CUIMinMap()
	{
		//	屬性設定
		_sx = _sy = 0;

		//	動畫設定
		_animas.reserve((int)Anima::ANIMACOUNT);
		for (int i = 0; i < (int)Anima::ANIMACOUNT; i++)
		{
			_animas.push_back(CAnimation());
		}
	}

	void CUIMinMap::SetRoom(RoomData ** rooms)
	{
		_rooms = rooms;
	}

	void CUIMinMap::OnMove()
	{
		if (_rooms == nullptr)
			return;
	}

	void CUIMinMap::OnShow()
	{
		if (_rooms == nullptr)
			return;
		vector<CAnimation>::iterator p;
		p = GetAnima(Anima::END);
		p->SetTopLeft(_sx, _sy);
		p->OnShow();
	}

	void CUIMinMap::LoadBitmap()
	{
		vector<CAnimation>::iterator p;
		p = GetAnima(Anima::NOTEXPLORED);
		p->AddBitmap(IDB_MinMap_NOTEXPLORED, RGB(255, 255, 255));
		p = GetAnima(Anima::EXPLORED);
		p->AddBitmap(IDB_MinMap_EXPLORED, RGB(255, 255, 255));
		p = GetAnima(Anima::PLAYERIN);
		p->AddBitmap(IDB_MinMap_Playerin, RGB(255, 255, 255));
		p = GetAnima(Anima::INIT);
		p->AddBitmap(IDB_MinMap_INIT, RGB(255, 255, 255));
		p = GetAnima(Anima::TREASURE);
		p->AddBitmap(IDB_MinMap_TREASURE, RGB(255, 255, 255));
		p = GetAnima(Anima::END);
		p->AddBitmap(IDB_MinMap_END, RGB(255, 255, 255));
		p = GetAnima(Anima::BOSS);
		p->AddBitmap(IDB_MinMap_END, RGB(255, 255, 255));
		p = GetAnima(Anima::AILSES);
		p->AddBitmap(IDB_MinMap_AILSES, RGB(255, 255, 255));
		p = GetAnima(Anima::AILSEH);
		p->AddBitmap(IDB_MinMap_AILSEH, RGB(255, 255, 255));
	}

	void CUIMinMap::SetXY(int x, int y)
	{
		_sx = x;
		_sy = y;
	}

	vector<CAnimation>::iterator CUIMinMap::GetAnima(Anima type)
	{
		return _animas.begin() + (int)type;
	}

	
}