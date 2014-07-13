#include "MemBlockListManager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

CMemBlockListManager::CMemBlockListManager()
:m_BlockCount(0)
{
    pListHead = NULL;
	pListTrail = NULL;
}
CMemBlockListManager::~CMemBlockListManager()
{
}

bool CMemBlockListManager::PushHead(MemBlock *pBlock)
{	
	if(NULL == pBlock)
	{
		return false;
	}

	if(pListHead == NULL)//the list is null, let head and trail equal pblock
	{
        pListHead = pBlock;
		pListTrail = pBlock;
		pListHead->pNext = NULL;
	}
	else
	{
		pBlock->pNext = pListHead;
		pListHead = pBlock;
	}
	return true;
}
bool CMemBlockListManager::PushTrail(MemBlock *pBlock)
{
	if(NULL == pBlock)
	{
		return false;
	}

	if(pListTrail == NULL)
	{
		pListHead = pBlock;
		pListTrail = pBlock;
	}
	else
	{
		pListTrail->pNext = pBlock;
		pListTrail = pBlock;
	}

	//test
	MemBlock *tmp;
	tmp = pListHead;
	while(tmp != NULL)
	{
		printf("push trailed:%d\n",tmp);
		tmp = tmp->pNext;
	}

	pListTrail->pNext = NULL;//reinit
	return true;
}
MemBlock *CMemBlockListManager::GetBlockHead()
{
	MemBlock *pRet = NULL;
	if(NULL == pListHead)
	{
		printf("getBlockHead,Head is null\n");
        return NULL;
	}

	pRet = pListHead;
	pListHead = pListHead->pNext;

	if(NULL == pListHead)// the list is null, the trai should  be null too
	{
		pListTrail = NULL;
	}

	return pRet;
}
MemBlock* CMemBlockListManager::AddrToBlock(char *addr)
{
	MemBlock *tmp = pListHead;
	while(tmp != NULL)
	{
		if(tmp->pBlock != NULL && tmp->pBlock == addr)
		{
			return tmp;
		}
	}
	return NULL;
}
MemBlock* CMemBlockListManager::DeletBlockWithAddr(char *addr)
{
	MemBlock *tmp = NULL, *front = pListHead;
	if(pListHead != NULL && pListHead->pBlock != NULL && pListHead->pBlock == addr)
	{
		tmp = pListHead;
		pListHead = pListHead->pNext;
		return tmp;
	}

    tmp = front->pNext;
	while(tmp != NULL)
	{
		if(tmp->pBlock != NULL && tmp->pBlock == addr)
		{
			 front->pNext = tmp->pNext;
			 return tmp;
		}

		front = tmp;
		tmp = tmp->pNext;
	}
    //the addr not in the list, return NULL
	return NULL;
}
bool CMemBlockListManager::IsEmpty()
{
	if(NULL == pListHead)
	{
		return true;
	}
	return false;
}