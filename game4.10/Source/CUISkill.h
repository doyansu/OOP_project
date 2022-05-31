#pragma once
#include "CUIButton.h"

namespace game_framework
{
	class CUISkill : public CUIButton
	{
	public:
		static CUISkill& Instance()
		{
			static CUISkill instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				instance.LoadBitmap();
				// 決定初始位置
				instance.SetTopLeft(SIZE_X - instance.Width(), SIZE_Y - instance.Height());
				isLoad = true;
			}
			return instance;
		}

		void SetValue(int percent);
		void ShowUI();

	protected:
		void LoadBitmap();
	private:
		int _percent;
		CAnimation _white, _blue, _backGround;
		CUISkill();

	};


}