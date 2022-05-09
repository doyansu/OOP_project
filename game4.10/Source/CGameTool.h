#pragma once

namespace game_framework
{
	class CGameTool
	{
	public:
		template<typename condition, typename source>	// �̱���M���Ӫ���
		static source FindObjBy(vector<source> objs, condition function)
		{
			for (source obj : objs)
			{
				if (function(obj))
					return obj;
			}
			return nullptr;
		}

		template<typename condition, typename source>	// �̱���M��h�Ӫ���
		static vector<source> FindObjsBy(vector<source> objs, condition function)
		{
			vector<source> result;
			result.reserve(objs.capacity());
			for (CGameObj* obj : objs)
			{
				if (function(obj))
					result.push_back(obj);
			}
			return result;
		}

		template<typename compare, typename source>	//	�̤���禡���̲ŦX����
		static vector<source> FindMaxObjBy(vector<source> objs, compare cmp)
		{
			source maxObj = objs.begin();
			for (CGameObj* obj : objs)
			{
				if (cmp(maxObj, obj))
					maxObj = obj;
			}
			return maxObj;
		}
	};
}


