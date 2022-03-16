namespace game_framework {

	class CGameObj
	{
	public:
		CGameObj();
		bool Collision(CGameObj *);
		int GetX1();
		int GetY1();
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
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
		CMovingBitmap _initbmp;		// ��l��
		int _x, _y, _moveSpeed;		// ��m�B���ʳt��
		bool _isMovingDown;			// �O�_���b���U����
		bool _isMovingLeft;			// �O�_���b��������
		bool _isMovingRight;			// �O�_���b���k����
		bool _isMovingUp;			// �O�_���b���W����

	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		void init();
	};
}