#ifndef IG_IMOUDLE_H
#define IG_IMOUDLE_H

class IGIMoudle
{
public:
	IGIMoudle() {}
	virtual ~IGIMoudle() {}

	virtual bool Awake() { return true; }		
	virtual bool Init() { return true; }
	virtual bool AfterInit() { return true; }
	virtual bool Update() { return true; }
	virtual bool Finalize() { return true; }
};

#endif // IG_IMOUDLE_H
