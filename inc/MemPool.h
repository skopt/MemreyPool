#ifndef _MEMPOOL_H_
#define _MEMPOOL_H_
/*------------------Include-------------------------*/
#include "DataStructDef.h"
#include "MemBlockListManager.h"
/*------------------Define-------------------------*/
struct ContnBlockInf
{
	MemBlock *pMemBlockList;
	char *pMemBlock;
	ContnBlockInf *pNext;
};

class CMemPool
{
public:
    CMemPool(int blockSize, int blockCount);
	~CMemPool();
	bool CreatPool();
	char* GetBlock();
    bool FreeBlock(char *addr);
private:
    virtual void FreeMem();
	ContnBlockInf* GetContnBlock(int blockSize, int blockCount);
public:
	int m_BlockCount;//current block size

	
private:
	long BlockSize;
	long BlockCount;
	bool CreatedFlag;
	ContnBlockInf *ContnBlockList;
	CMemBlockListManager FreeList;           
	CMemBlockListManager UsedList;

};


#endif
