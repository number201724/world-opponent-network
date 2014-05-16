#include "ByteBuffer.h"
using namespace WONAPI;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ByteBuffer::ByteBuffer() : mData(NULL), mDataLen(0)
{	
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ByteBuffer::ByteBuffer(const char *theStr)
{
	if(theStr==NULL)
	{
		mData = NULL;
		mDataLen = 0;
	}
	else
	{
		mDataLen = strlen(theStr)+1;
		mData = new char[mDataLen];
		memcpy(mData,theStr,mDataLen);
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ByteBuffer::ByteBuffer(const void *theData, unsigned long theLen, bool takeOwnership) 
{
	if(takeOwnership)
	{
		mData = (char*)theData;
		mDataLen = theLen;
	}
	else
	{
		mData = new char[theLen];
		mDataLen = theLen;

		if(theLen>0)
			memcpy(mData,theData,theLen);
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ByteBuffer::~ByteBuffer()
{
	delete[] mData;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
OffsetByteBuffer::OffsetByteBuffer(void *theBeginData, unsigned long theOffset, unsigned long theDataLen) :
	ByteBuffer(((char*)theBeginData)+theOffset,theDataLen,true)
{
	mBeginData = (char*)theBeginData;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
OffsetByteBuffer::~OffsetByteBuffer()
{
	delete [] mBeginData;
	mData = NULL; // so ~ByteBuffer doesn't delete mData
}
