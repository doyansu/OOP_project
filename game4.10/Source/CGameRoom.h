#pragma once

namespace game_framework
{
	class CGameRoom
	{
	public:
		enum class RoomType {NULLANY, NORMAL, TREASURE};
		CGameRoom();
	protected:
		int _centerX, _centerY;
		int _weight, _height;
	private:

	};
}