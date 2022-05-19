#pragma once


namespace game_framework
{
	class CUIButton : public CAnimation
	{
	public:
		CUIButton()
		{

		}

		bool  PointIn(int x, int y)
		{
			return x > this->Left() && x < this->Left() + this->Width() && y > this->Top() && y < this->Top() + this->Height();
		}
	};
}