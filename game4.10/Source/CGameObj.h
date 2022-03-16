namespace game_framework {

	class CGameObj
	{
	public:
		CGameObj();
		bool Collision(CGameObj *);
		int GetX1();
		int GetY1();
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int, int);
		void SetSpeed(int);

		virtual int GetX2();
		virtual int GetY2();
		virtual void LoadBitmap(int);
		virtual void OnShow();
		virtual void OnMove();
		virtual void OnKeyUp(char);
		virtual void OnKeyDown(char);

	protected:
		CMovingBitmap _initbmp;		// 初始圖
		int _x, _y, _moveSpeed;		// 位置、移動速度
		bool _isMovingDown;			// 是否正在往下移動
		bool _isMovingLeft;			// 是否正在往左移動
		bool _isMovingRight;			// 是否正在往右移動
		bool _isMovingUp;			// 是否正在往上移動

	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		void init();
	};
}