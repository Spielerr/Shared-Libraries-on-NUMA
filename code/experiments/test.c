#include <stdio.h>
#include <time.h>
#include<x86intrin.h>

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  	{_mm_clflush(arr);
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
{_mm_clflush(arr);
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); }}
} 

int main()
{
clock_t start, end;
double cpu_time_used;

int a[9999];
start = clock();
		
for(int i=0; i<9999;i++)
{
a[i] = i+1;
}
_mm_clflush(a);
int n = sizeof(a)/sizeof(a[0]); 
    bubbleSort(a, n);

end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("Time taken is %lf\n",cpu_time_used);
}
