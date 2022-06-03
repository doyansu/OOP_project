#pragma once

namespace game_framework
{
	class CGameTimer
	{
	friend class CGameState;
	public:
		CGameTimer();

		void SetStartPoint(int);			//	�]�w�p�ɰ_�I
		int GetStartPoint();				//	���o�p�ɰ_�I
		int GetTimingTime();				//	���o�p�ɮɶ�

		static CGameTimer& Instance();		//	��@��K����p��
		static int CurrentTime();			//	���o��e�ɶ�
		static int ConvertToSeconds(int);	//	�ন���

	protected:
		void Timing();						//	�b CGameState �p�ɷ�e�ɶ�

	private:
		int _startPoint;					//	�p�ɰ_�I
		static int _currentTime;			//	��e�ɶ�
	};

}