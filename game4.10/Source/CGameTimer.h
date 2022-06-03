#pragma once

namespace game_framework
{
	class CGameTimer
	{
	friend class CGameState;
	public:
		CGameTimer();

		void SetStartPoint(int);			//	設定計時起點
		int GetStartPoint();				//	取得計時起點
		int GetTimingTime();				//	取得計時時間

		static CGameTimer& Instance();		//	實作方便全域計數
		static int CurrentTime();			//	取得當前時間
		static int ConvertToSeconds(int);	//	轉成秒數

	protected:
		void Timing();						//	在 CGameState 計時當前時間

	private:
		int _startPoint;					//	計時起點
		static int _currentTime;			//	當前時間
	};

}