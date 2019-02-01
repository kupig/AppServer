#ifndef IG_INET_MOUDLE_H
#define IG_INET_MOUDLE_H

#include "../IGInterface/IGIMoudle.h"

class IGINetMoudle
	: public IGIMoudle
{
public:
	virtual void CreateServerNet(int port) = 0;	
	virtual void RemoveServerNet() = 0;

	// virtual void CreateClientNet();
	// virtual void RemoveClientNet();
};

#endif // IG_INET_MOUDLE_H
