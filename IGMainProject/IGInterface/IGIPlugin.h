#ifndef IG_IPLUGIN_H
#define IG_IPLUGIN_H

class IGIPlugin
{
public:
	IGIPlugin() {}
	virtual ~IGIPlugin() {}

	virtual bool Awake() { return true; }	
	virtual bool Init() { return true; }
	virtual bool AfterInit() { return true; }
	virtual bool Update() { return true; }
	virtual bool Finalize() { return true; }
};

#endif // IG_IPLUGIN_H
