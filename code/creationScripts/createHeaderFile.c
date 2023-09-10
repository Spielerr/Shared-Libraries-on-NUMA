#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE* fp;
	fp = fopen("sharedLibrary.h","w");
	
	for(int i=1; i<=800000; i++)
	{
		fprintf(fp,"int f_%d();\n",i);
	}
	
	fclose(fp);
	
	return 0;
}
