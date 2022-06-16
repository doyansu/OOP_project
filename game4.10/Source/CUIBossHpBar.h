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
				// �M�w��l��m
				instance.SetTopLeft((SIZE_X - instance.Width()) / 2, 10);
				isLoad = true;
			}
			return instance;
		}

		void SetEnable(bool);
		void SetPercent(int);
		void ShowHpBar();

	private:
		bool _enable;		//	�O�_��� UI
		int _percent;		//	�ʤ���
		CAnimation _fill;	//	��R�ʵe

		CUIBossHpBar();
		void LoadBitmap();

	};

}