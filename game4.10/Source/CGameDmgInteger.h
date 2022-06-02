#pragma once

namespace game_framework 
{
	class CGameDmgInteger : public CInteger
	{
	public:
		CGameDmgInteger();
		
		bool IsSurvive();
		void SetSurviveTime(int);
		void AddDmg(int);
		void OnShow();
		void Kill();

	private:
		int _surviveTime;		// 計數
		int _survive;	// 存活時間
	};

}