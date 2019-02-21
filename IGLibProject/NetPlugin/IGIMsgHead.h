#ifndef IG_IMSG_HEAD
#define IG_IMSG_HEAD

#include <string.h>
#include <assert.h>

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
	virtual void SetMsgID(uint16_t msgId) = 0;

	virtual int GetBodyLen() = 0;
	virtual void SetBodyLen(uint32_t size) = 0;
};

class IGCMsgHead : public IGIMsgHead
{
public:
	IGCMsgHead() : mBodySize(0), mMsgID(0) {}
	virtual ~IGCMsgHead() {}	

	virtual int EnCode(char *data)
	{
		int offset = 0;
		
		// msgID = 2Byte		
		uint16_t msgId = htons(mMsgID);	
		memcpy(data + offset, (void *)&msgId, sizeof(uint16_t));
		offset += sizeof(uint16_t);

		// msg size = 4Byte
		uint32_t packSize = mBodySize + IG_HEAD_LENGTH;
		uint32_t size = htobe32(packSize);
		memcpy(data + offset, (void *)&size, sizeof(uint32_t));
		offset += sizeof(uint32_t);	

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
		mMsgID = be16toh(msgId);	
		offset += sizeof(msgId);

		// msg size = 4Byte
		uint32_t packSize = 0;
		memcpy(&packSize, data + offset, sizeof(packSize));	
		mBodySize = be32toh(packSize) - IG_HEAD_LENGTH;
		offset += sizeof(packSize);

		if (offset != IG_HEAD_LENGTH)
		{
			assert(0);
		}

		return offset;
	}

	virtual int GetMsgID() { return mMsgID;}
	virtual void SetMsgID(uint16_t msgId) { mMsgID = msgId; }

	virtual int GetBodyLen() {return mBodySize;}
	virtual void SetBodyLen(uint32_t size) {mBodySize = size;}

private:
	uint32_t mBodySize;
	uint16_t mMsgID;
};
#pragma pack(pop)

#endif // IG_IMSG_HEAD
