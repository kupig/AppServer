#ifndef IG_MAP_H
#define IG_MAP_H

#include <map>
#include <string>

template<class T, class D>
class IGMap
{
public:
	typedef std::map<T, D*> IGMAPOBJECT;	
	typedef std::map<T, D*>::iterator IGMAPOBJECT_ITER;

	IGMap() {}
	virtual ~IGMap() {}

	bool Add(const T& name, D* data)
	{
		bool ret = false;

		IGMAPOBJECT_ITER iter = mMapObject.find(name);
		if (iter == mMapObject.end())
		{
			mMapObject.insert(IGMAPOBJECT::value_type(name, data);
			ret = true;			
		}
		
		return ret;
	}

	D* Remove(const T& name)
	{
		D* pData = NULL;
		
		IGMAPOBJECT_ITER iter = mMapObject.find(name);
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
	IGMAPOBJECT_ITER mCurrObjectIter;	
};

#endif //IG_MAP_H

