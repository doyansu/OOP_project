#pragma once
#include "CGameWeapon.h"
#include "CGameFactorys.h"


namespace game_framework {
	template <class ProductBase_t, class ProductType_t>
	class WeaponRegistrar : public IProductRegistrar<ProductBase_t>
	{
	public:
		// ���U���~��u�t
		WeaponRegistrar(int name)
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
			static WeaponRegistrar<CGameWeapon, CGameWeapon_Init> Register1((int)CGameWeapon::Type::INIT);
		}
	};


	class CGameWeapon_Init : public CGameWeapon
	{
	public:
		static CGameWeapon_Init& Instance()
		{
			static CGameWeapon_Init Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}

		CGameWeapon_Init();
		void LoadBitmap();
	protected:
		
	private:
		
	};

}