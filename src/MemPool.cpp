#include "MemPool.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

CMemPool::CMemPool(int blockSize,int blockCount)
:BlockSize(blockSize),BlockCount(blockCount),m_BlockCount(0),CreatedFlag(false)
{

}
CMemPool::~CMemPool()
{
	FreeMem();
}
//creat the pool according to the param
bool CMemPool::CreatPool()
{
	if(BlockSize <= 0 || BlockCount <= 0 || CreatedFlag)
	{
		return false;
	}

	//get a continue memery block	
	ContnBlockList = GetContnBlock(BlockSize,BlockCount);
	if(NULL == ContnBlockList)
	{
		printf("get continue block failed");
		return false;
	}
	MemBlock *block = ContnBlockList->pMemBlockList, *tmp = NULL;
	while(block != NULL)
	{
		printf("tmp=%d\n",tmp);
		tmp = block->pNext;
		FreeList.PushTrail(block);
		block = tmp;
		printf("tmp=%d\n",tmp);
	}

    m_BlockCount += BlockCount;
	CreatedFlag = true;
	return true;
}
char* CMemPool::GetBlock()
{
	MemBlock *pRet;
	pRet = FreeList.GetBlockHead();
	if(pRet == NULL)
	{
		printf("get block failed");
		return NULL;
	}

	UsedList.PushTrail(pRet);
	memset(pRet->pBlock, 0, BlockSize); 
	return pRet->pBlock;	
}

bool CMemPool::FreeBlock(char *addr)
{
	MemBlock *block = UsedList.DeletBlockWithAddr(addr);
	if(NULL == block)
	{
		printf("FreeBlock error: get block null");
		return false;
	}
	//init the block
	block->pNext = NULL;
	memset(block->pBlock, 0, BlockSize);

	FreeList.PushTrail(block);
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
		printf("next is=%d\n", pContnBlock->pMemBlockList[i].pNext);
    }
	MemBlock *tmp = pContnBlock->pMemBlockList;
	while(tmp != NULL)
	{
		printf("tmp = %d\n", tmp);
		tmp = tmp->pNext;
	}

	return pContnBlock;	
}
