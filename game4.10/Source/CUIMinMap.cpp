#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CUIMinMap.h"

namespace game_framework
{
	CUIMinMap::CUIMinMap(RoomData ** rooms)
	{
		//	屬性設定
		if (rooms != nullptr)
			_rooms = rooms;
		_sx = _sy = 0;

		//	動畫設定
		_animas.reserve((int)Anima::ANIMACOUNT);
		for (int i = 0; i < (int)Anima::ANIMACOUNT; i++)
		{
			_animas.push_back(CAnimation());
		}
	}

	void CUIMinMap::OnMove()
	{

	}

	void CUIMinMap::OnShow()
	{

	}

	void CUIMinMap::LoadBitmap()
	{

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