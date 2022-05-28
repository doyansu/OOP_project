#pragma once

namespace game_framework
{
	class CAnimationEnemyAppear : public CAnimation
	{
	public:
		static CAnimationEnemyAppear& Instance()
		{
			static CAnimationEnemyAppear instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				instance.SetDelayCount(2);
				instance.AddBitmap(IDB_enemyAppearance_0, RGB(0, 0, 0));
				instance.AddBitmap(IDB_enemyAppearance_1, RGB(0, 0, 0));
				instance.AddBitmap(IDB_enemyAppearance_2, RGB(0, 0, 0));
				instance.AddBitmap(IDB_enemyAppearance_3, RGB(0, 0, 0));
				instance.AddBitmap(IDB_enemyAppearance_4, RGB(0, 0, 0));
				isLoad = true;
			}
			return instance;
		}

	private:
		CAnimationEnemyAppear() {};
	};

}