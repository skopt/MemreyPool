#ifndef _MEMPOOL_H_
#define _MEMPOOL_H_
/*------------------Define-------------------------*/
struct MemBlock
{
	MemBlock *pNext;
	char *pBlock;
};
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
	MemBlock* GetBlock();
    bool FreeBlock(MemBlock *pBlock);
private:
    virtual void FreeMem();
	ContnBlockInf* GetContnBlock(int blockSize, int blockCount);
	
public:
	int m_BlockCount;//current block size

	
private:
	long BlockSize;
	long BlockCount;
	ContnBlockInf *ContnBlockList;
	MemBlock *FreeListHead;
	MemBlock *FreeListTrail;

};


#endif