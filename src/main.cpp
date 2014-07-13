#include "MemPool.h"
#include <stdio.h>


int main()
{
    CMemPool TestPool(100, 3);
	TestPool.CreatPool();
	char *pTmp;
	for(int i = 0; i < 3; i++)
	{
		pTmp = TestPool.GetBlock();
		if(pTmp != NULL)
		    printf("get memery %d, dest=%02x\n", i, pTmp);
		else
			printf("get error\n");
	}
	return 1;
}
