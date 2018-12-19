#ifndef IG_SINGLETON_H
#define IG_SINGLETON_H

template <class T>
class IGSingleton
{
public:
static T& Instance() {
		static T theIGSingleton;
		return theIGSingleton;
	}
protected:
	IGSingleton() {}
	IGSingleton(IGSingleton const &) {}
	IGSingleton& operator=(IGSingleton const &) {}
	virtual ~IGSingleton() {}
};


#endif // IG_SINGLETON_H
