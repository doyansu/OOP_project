#pragma once

//https://zhuanlan.zhihu.com/p/83537599

namespace game_framework
{
	template <class ProductType_t>
	class IProductRegistrar
	{
	public:
		virtual ProductType_t *CreateProduct() = 0;

	protected:
		IProductRegistrar() {}
		virtual ~IProductRegistrar() {}

	private:
		IProductRegistrar(const IProductRegistrar &);
		const IProductRegistrar &operator=(const IProductRegistrar &) {};
	};

	template <class ProductType_t>
	class ProductFactory
	{
	public:
		static ProductFactory<ProductType_t> &Instance()
		{
			static ProductFactory<ProductType_t> instance;
			return instance;
		}

		// 產品註冊
		void RegisterProduct(IProductRegistrar<ProductType_t> *registrar, std::string name)
		{
			m_ProductRegistry[name] = registrar;
		}

		// 
		ProductType_t *GetProduct(std::string name)
		{
			if (m_ProductRegistry.find(name) != m_ProductRegistry.end())
			{
				return m_ProductRegistry[name]->CreateProduct();
			}

			return NULL;
		}

	private:
		ProductFactory() {}
		~ProductFactory() {}

		ProductFactory(const ProductFactory &);
		const ProductFactory &operator=(const ProductFactory &) {};

		// 保存註冊過的產品，key:產品名字，value:產品類型
		std::map<std::string, IProductRegistrar<ProductType_t> *> m_ProductRegistry;
	};

	// ProductBase_t 是產品的 BaseClass, ProductType_t 是產品的類別
	template <class ProductBase_t, class ProductType_t>
	class ProductRegistrar : public IProductRegistrar<ProductBase_t>
	{
	public:
		// 註冊產品到工廠
		explicit ProductRegistrar(string name)
		{
			ProductFactory<ProductBase_t>::Instance().RegisterProduct(this, name);
		}

		// 創建產品
		ProductBase_t *CreateProduct()
		{
			return new ProductType_t();
		}
	};
}