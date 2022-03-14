namespace game_framework {

	class CGate
	{
	public:
		CGate();
		bool HitPlayer(CInitialPlayer *player);						// �O�_�I�����l
		void LoadBitmap();										// ���J�ϧ�
		void OnShow();											// �N�ϧζK��e��
		void Initialize();								// �]�w��ߪ��y��

	protected:
		CMovingBitmap bmp;			
		int x, y;					

	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}