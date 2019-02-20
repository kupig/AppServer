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
		
		return offset;
	}

	virtual int DeCode(const char *data)
	{
		uint32_t offset = 0;
		
		// msgId = 2Byte
		uint16_t msgId = 0;
		memcpy(&msgId, data + offset, sizeof(msgId));
		mMsgId = be16toh(msgId);	
		offset += sizeof(msgId);

		// msg size = 4Byte
		uint32_t packSize = 0;
		memcpy(&packSize, data + offset, sizeof(packSize));	
		mSize = be32toh(data);
		offset += sizeof(packSize);

		if (offset != IG_HEAD_LENGTH)
		{
			assert(0);
		}

		return offset;
	}

	virtual int GetMsgID() { return mMsgId;}
	virtual void SetMsgID(uint16_t msgId) { mMsgId = msgId; }

	virtual int GetBodyLen() {return mSize;}
	virtual int SetBodyLen(uint32_t size) {mSize = size;}

private:
	uint32_t mSize;
	uint16_t mMsgID;
};
#pragma pack(pop)

#endif // IG_IMSG_HEAD
