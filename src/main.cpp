#include "MemPool.h"
#include <stdio.h>


int main()
{
    CMemPool TestPool(100, 64);
	TestPool.CreatPool();
	MemBlock *pTmp;
	for(int i = 0; i < 65; i++)
	{
		pTmp = TestPool.GetBlock();
		if(pTmp != NULL)
		    printf("get memery %d, dest=%d\n", i, pTmp->pBlock);
		else
			printf("get error\n");
	}
	return 1;
}
