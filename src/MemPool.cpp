#include "MemPool.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

CMemPool::CMemPool(int blockSize,int blockCount)
:BlockSize(blockSize),BlockCount(blockCount),m_BlockCount(0)
{
    FreeListHead = NULL;
	FreeListTrail = NULL;
}
CMemPool::~CMemPool()
{
	FreeMem();
}
//creat the pool according to the param
bool CMemPool::CreatPool()
{
	if(BlockSize <= 0 || BlockCount <= 0 || FreeListHead != NULL)
	{
		return false;
	}

	//get a continue memery block	
	ContnBlockList = GetContnBlock(BlockSize,BlockCount);
	if(NULL == ContnBlockList)
	{
		return false;
	}
	FreeListHead = ContnBlockList->pMemBlockList;
	FreeListTrail = FreeListHead;
    m_BlockCount += BlockCount;
	return true;
}
MemBlock* CMemPool::GetBlock()
{
	MemBlock* pTmp, *pRet;
	if(FreeListHead == NULL)
	{
		return NULL;
	}

	pTmp = FreeListHead->pNext;
	pRet = FreeListHead;
	pRet->pNext = NULL;
	FreeListHead = pTmp;

	return pRet;	
}

bool CMemPool::FreeBlock(MemBlock *Block)
{
	//init the block
	Block->pNext = NULL;
	memset(Block->pBlock, 0, BlockSize);
	if(NULL == FreeListTrail)
	{
		FreeListTrail = Block;
		FreeListHead = FreeListTrail;
	}
	else
	{
		FreeListTrail->pNext = Block;
		FreeListTrail = Block;
	}

	return true;
}

/*****************not public*************************/
void CMemPool::FreeMem()
{
	ContnBlockInf * pTmp = ContnBlockList, *pConBlockNext;
	while(pTmp != NULL)
	{
		pConBlockNext = pTmp->pNext;

		delete[] pTmp->pMemBlock;
		delete[] pTmp->pMemBlockList;
		delete pTmp;
		
		pTmp = pConBlockNext;
	}	
}
ContnBlockInf* CMemPool::GetContnBlock(int blockSize, int blockCount)
{
	if(blockCount <= 0 || blockSize <= 0)
	{
		return NULL;
	}
	//get block info struct
	ContnBlockInf *pContnBlock =new ContnBlockInf();
	if(NULL == pContnBlock)
	{
		return NULL;
	}	
	memset(pContnBlock, 0, sizeof(pContnBlock));

	//get mem block
	pContnBlock->pMemBlock = new char[blockSize * blockCount];
	if(NULL == pContnBlock->pMemBlock)
	{
		delete pContnBlock;
		return NULL;
	}
	memset(pContnBlock->pMemBlock, 0, sizeof(pContnBlock->pMemBlock));

	//get mem list
	pContnBlock->pMemBlockList = new MemBlock[blockCount];
	if(NULL == pContnBlock->pMemBlockList)
	{
		delete pContnBlock->pMemBlock;
		delete pContnBlock;
		return NULL;
	}
	memset(pContnBlock->pMemBlockList, 0, sizeof(pContnBlock->pMemBlockList));

    //init
    for(int i = 0; i < blockCount; i++)
    {
		pContnBlock->pMemBlockList[i].pBlock =(char *)(&(pContnBlock->pMemBlock[i*BlockSize]));
        if(i != blockCount - 1)//it's null when i = blockcount-1 because the init before
        {
		    pContnBlock->pMemBlockList[i].pNext = &(pContnBlock->pMemBlockList[i+1]);
        }
    }

	return pContnBlock;	
}

