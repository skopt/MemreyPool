#include "MemPool.h"
#include <stdio.h>


int main()
{
    CMemPool TestPool(100, 3, 2);
	TestPool.CreatPool();
	char *pTmp0,*pTmp1,*pTmp2,*pTmp3;
	pTmp0 = TestPool.GetBlock();
	pTmp1 = TestPool.GetBlock();
	pTmp2 = TestPool.GetBlock();
	pTmp3 = TestPool.GetBlock();

	TestPool.FreeBlock(pTmp3);
	TestPool.FreeBlock(pTmp1);
	TestPool.FreeBlock(pTmp0);
	TestPool.FreeBlock(pTmp2);
	
	
	return 1;
}
