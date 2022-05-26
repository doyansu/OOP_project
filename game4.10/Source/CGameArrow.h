#pragma once

namespace game_framework
{
	class CGameArrow : public CAnimation
	{
	public:
		static CGameArrow& Instance()
		{
			static CGameArrow instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				instance.SetDelayCount(2);
				instance.AddBitmap(IDB_ItemArrow_0, RGB(0, 0, 0));
				instance.AddBitmap(IDB_ItemArrow_1, RGB(0, 0, 0));
				instance.AddBitmap(IDB_ItemArrow_2, RGB(0, 0, 0));
				instance.AddBitmap(IDB_ItemArrow_3, RGB(0, 0, 0));
				instance.AddBitmap(IDB_ItemArrow_4, RGB(0, 0, 0));
				instance.AddBitmap(IDB_ItemArrow_5, RGB(0, 0, 0));
				instance.AddBitmap(IDB_ItemArrow_4, RGB(0, 0, 0));
				instance.AddBitmap(IDB_ItemArrow_3, RGB(0, 0, 0));
				instance.AddBitmap(IDB_ItemArrow_2, RGB(0, 0, 0));
				instance.AddBitmap(IDB_ItemArrow_1, RGB(0, 0, 0));
				isLoad = true;
			}
			return instance;
		}
		
	private:
		CGameArrow();
	};
}