#pragma once

namespace game_framework
{
	class CGameRoom
	{
	public:
		enum class RoomType {NULLANY, NORMAL, TREASURE};
		CGameRoom();
		int CenterX();
		int CenterY();
		int Width();
		int High();

	protected:
		int _centerX, _centerY;
		int _width, _high;
	private:

	};
}