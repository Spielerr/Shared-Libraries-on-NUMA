#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE* fp;
	fp = fopen("sharedLibrary.c","w");
	
	for(int i=1; i<=800000; i++)
	{
		fprintf(fp,"int f_%d() { if(%d&1 == 0) return %d; else return %d-1; }\n",i,i,i,i);
	}
	
	fclose(fp);
	
	return 0;
}
