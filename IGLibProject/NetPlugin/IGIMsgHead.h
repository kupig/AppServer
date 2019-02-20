#ifndef IG_IMSG_HEAD
#define IG_IMSG_HEAD

#pragma pack(push, 1)

class IGIMsgHead
{
public:
	enum IG_Head
	{
		IG_HEAD_LENGTH = 6,
	};

	virtual int EnCode(const char *data) = 0;
	virtual int DeCode(const char *data) = 0;		
	
	virtual int GetMsgID() = 0;
	virtual void SetMsgID() = 0;

	virtual int GetBodyLen() = 0;
	virtual void SetBodyLen() = 0;
};

class IGCMsgHead : public IGIMsgHead
{
public:
	IGCMsgHead() {}
	virtual ~IGCMsgHead() {}	

	virtual int EnCode(const char *data)
	{
		int nOffset = 0;
		
	}
};
#pragma pack(pop)

#endif // IG_IMSG_HEAD
