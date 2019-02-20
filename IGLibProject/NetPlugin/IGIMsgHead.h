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

	virtual int EnCode(char *data) = 0;
	virtual int DeCode(const char *data) = 0;		
	
	virtual int GetMsgID() = 0;
	virtual void SetMsgID() = 0;

	virtual int GetBodyLen() = 0;
	virtual void SetBodyLen() = 0;
};

class IGCMsgHead : public IGIMsgHead
{
public:
	IGCMsgHead() : mSize(0), mMsgID(0) {}
	virtual ~IGCMsgHead() {}	

	virtual int EnCode(char *data)
	{
		int offset = 0;
		
		// msgID = 2Byte		
		uint16_t msgId = htons(mMsgID);	
		memcpy(data + offset, (void *)&mMsgID, sizeof(mMsgID));
		offset += sizeof(mMsgID);

		// msg size = 4Byte
		uint32_t packSize = mSize + IG_HEAD_LENGTH;
		uint32_t msgSize = htobe32(packSize);
		memcpy(data + offset, (void *)&msgSize, sizeof(msgSize));
		offset += sizeof(msgSize);	

		if (offset != IG_HEAD_LENGTH)
		{
			assert(0);	
		}
	}

	virtual int DeCode(const char *data)
	{
	}

private:
	uint32_t mSize;
	uint16_t mMsgID;
};
#pragma pack(pop)

#endif // IG_IMSG_HEAD
