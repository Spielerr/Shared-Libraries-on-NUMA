#include <stdint.h>
#include <x86intrin.h>
#include <stdio.h>

int main()
{

  //unsigned int aux;
  uint64_t time1, time2, msl, osl; /* initial values don't matter */

  /* You can generally use rdtsc or rdtscp.
     See: https://stackoverflow.com/questions/59759596/is-there-any-difference-in-between-rdtsc-lfence-rdtsc-and-rdtsc-rdtscp
     I AM NOT SURE THOUGH THAT THE SERIALIZATION PROERTIES OF
     RDTSCP ARE APPLICABLE AT THE COMPILER LEVEL WHEN USING THE
     __RDTSCP INTRINSIC. THIS IS TRUE FOR PURE FENCES SUCH AS LFENCE. */

  _mm_mfence();                      /* this properly orders both clflush and rdtsc*/
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtsc */
  time1 = __rdtsc();                 /* set timer */
  _mm_lfence();                      /* serialize __rdtsc with respect to trailing instructions + compiler barrier for rdtsc and the load */
  int t1 = f_150000();             /* array[0] is a cache miss */
  int t2 = f_300000();  
  int t3 = f_149999();             /* array[0] is a cache miss */
  int t4 = f_299999(); 
  int t5 = f_149998();             /* array[0] is a cache miss */
  int t6 = f_299998();
  int t7 = f_149997();             /* array[0] is a cache miss */
  int t8 = f_299997(); 
  /* measring the write miss latency to array is not meaningful because it's an implementation detail and the next write may also miss */
  /* no need for mfence because there are no stores in between */
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtsc and the load*/
  time2 = __rdtsc();
  _mm_lfence();                      /* serialize __rdtsc with respect to trailing instructions */
  msl = time2 - time1;

  printf( "%d,%d,%d,%d,%d,%d,%d,%d\n", t1,t2,t3,t4,t5,t6,t7,t8 );             /* prevent the compiler from optimizing the load */
  printf( "miss section latency = %lu \n", msl );   /* the latency of everything in between the two rdtsc */

  _mm_mfence();                      /* this properly orders both clflush and rdtsc */
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtsc */
  time1 = __rdtsc();                 /* set timer */
  _mm_lfence();                      /* serialize __rdtsc with respect to trailing instructions + compiler barrier for rdtsc */
  /* no need for mfence because there are no stores in between */
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtsc */
  time2 = __rdtsc();
  _mm_lfence();                      /* serialize __rdtsc with respect to trailing instructions */
  osl = time2 - time1;

  printf( "overhead latency = %lu \n", osl ); /* the latency of everything in between the two rdtsc */

  printf( "Measured main memory latency = %lu TSC cycles\n", msl - osl ); /* msl is always larger than osl and hsl */

  return 0;
}
