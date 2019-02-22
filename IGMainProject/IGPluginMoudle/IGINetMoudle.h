#ifndef IG_INET_MOUDLE_H
#define IG_INET_MOUDLE_H

#include "../IGInterface/IGIMoudle.h"
#include "../../IGLibProject/NetPlugin/IGNetInterface.h"

class IGINetMoudle
	: public IGIMoudle
{
public:
	virtual void CreateServerNet(int port) = 0;	
	virtual void RemoveServerNet() = 0;

	// virtual void CreateClientNet();
	// virtual void RemoveClientNet();
	
	virtual bool ReMsgCB(int msgId, NET_RECIEVE_FUNCTION_PTR &msgFuncCB) = 0;

	template <typename T>
	bool ReMsgCB(int msgId, T *t, void (T::*Handle)(int fd, int msgId, const char* msg, unsigned int len))
	{
		NET_RECIEVE_FUNCTION func = 
			std::bind(Handle, t, std::placeholders::_1, 
			std::placeholders::_2, std::placeholders::_3, 
			std::placeholders::_4);	

		NET_RECIEVE_FUNCTION_PTR funcPtr(new NET_RECIEVE_FUNCTION(func));
		
		return ReMsgCB(msgId, funcPtr);
	}
};

#endif // IG_INET_MOUDLE_H
