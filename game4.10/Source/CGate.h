namespace game_framework {

	class CGate
	{
	public:
		CGate();
		bool HitPlayer(CInitialPlayer *player);						// 是否碰到擦子
		void LoadBitmap();										// 載入圖形
		void OnShow();											// 將圖形貼到畫面
		void Initialize();								// 設定圓心的座標

	protected:
		CMovingBitmap bmp;			
		int x, y;					

	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}