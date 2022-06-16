#pragma once


namespace game_framework
{
	class CUIBossHpBar : public CAnimation
	{
	public:
		static CUIBossHpBar& Instance()
		{
			static CUIBossHpBar instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				instance.LoadBitmap();
				// 決定初始位置
				instance.SetTopLeft((SIZE_X - instance.Width()) / 2, 10);
				isLoad = true;
			}
			return instance;
		}

		void SetEnable(bool);
		void SetPercent(int);
		void ShowHpBar();

	private:
		bool _enable;		//	是否顯示 UI
		int _percent;		//	百分比
		CAnimation _fill;	//	填充動畫

		CUIBossHpBar();
		void LoadBitmap();

	};

}