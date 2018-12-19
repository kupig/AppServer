#ifndef IG_MAP_H
#define IG_MAP_H

#include <map>
#include <string>

template<typename T, typename D>
class IGMap
{
public:
	typedef std::map<T, D*> IGMAPOBJECT;	

	IGMap() {}
	virtual ~IGMap() {}

	bool Add(const T& name, D* data)
	{
		bool ret = false;

		typename IGMAPOBJECT::iterator iter = mMapObject.find(name);
		if (iter == mMapObject.end())
		{
			mMapObject.insert(typename IGMAPOBJECT::value_type(name, data));
			ret = true;			
		}
		
		return ret;
	}

	D* Remove(const T& name)
	{
		D* pData = NULL;
		
		typename IGMAPOBJECT::iterator iter = mMapObject.find(name);
		if (iter != mMapObject.end())
		{
			pData = iter->second;
			mMapObject.erase(iter);	
		}

		return pData;
	}
	
	D* First()
	{
		D* pData = NULL;
		if (mMapObject.size() > 0)
		{
			mCurrObjectIter = mMapObject.begin();			
			pData = mCurrObjectIter->second;
		}
		
		return pData;
	}
	
	D* Next()
	{
		D* pData = NULL;

		if (++mCurrObjectIter != mMapObject.end())
		{
			pData = mCurrObjectIter->second; 	
		}	
		
		return pData;
	}

private:
	IGMAPOBJECT mMapObject;
	typename IGMAPOBJECT::iterator mCurrObjectIter;
};

#endif //IG_MAP_H

