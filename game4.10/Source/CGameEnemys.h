#pragma once
#include "CEnemy.h"
#include "CGameFactorys.h"

namespace game_framework
{
	template <class ProductBase_t, class ProductType_t>
	class EnemyRegistrar : public IProductRegistrar<ProductBase_t>
	{
	public:
		// ���U���~��u�t
		EnemyRegistrar(int name)
		{
			ProductFactory<ProductBase_t>::Instance().RegisterProduct(this, name);
		}

		// �Ыز��~
		ProductBase_t* CreateProduct()
		{
			return new ProductType_t(ProductType_t::Instance());
		}

		// Factory ���U
		static void Register()
		{
			static EnemyRegistrar<CEnemy, CGameEnemy_Init> Register1((int)CEnemy::Type::INIT);
		}
	};

	class CGameEnemy_Init : public CEnemy
	{
	public:
		static CGameEnemy_Init& Instance()
		{
			static CGameEnemy_Init Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}

		CGameEnemy_Init();
		void LoadBitmap();
	protected:

	private:

	};
}
