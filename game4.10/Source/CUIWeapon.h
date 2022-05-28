#pragma once

namespace game_framework
{
	class CUIWeapon : public CAnimation
	{
	public:
		static CUIWeapon& Instance()
		{
			static CUIWeapon instance; 
			static bool isLoad = false;
			if (isLoad == false)
			{
				instance.AddBitmap(IDB_BACKGROUND);
				isLoad = true;
			}
			return instance;
		}

		void SetValue(int atk, int cost, int crit, int spread);
		void SetMove(bool moveDown = true);
		void MoveUI();
		void ShowUI();

	protected:
		

	private:
		int _dy;
		int _atk, _cost, _crit, _spread;
		bool _moveDown;
		CUIWeapon();
		
	};


}
