#include <stdio.h>
using namespace std;

/* Gotta read fast */
#define BSIZE 1<<15
char buffer[BSIZE];
long bpos = 0L, bsize = 0L; 
long readLong()
{
	long d = 0L, x = 0L;
	char c;

	while (1)
  {
		if (bpos >= bsize)
    {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
		else if (d == 1) return x;
	} 
	return -1;
}
 
#define Nmax 20000
#define Kmax 1000000
int pop[Nmax];
int min_length_of_sum[Kmax + 1];
int main()
{ 
  /* Read input and save population of building i at pop[i] */
  int N, K;
  N = readLong();
  K = readLong();
  for (int i = 0; i < N; i++)
  {
    pop[i] = readLong();
    if (pop[i] == K)
    {
      printf("%i\n", 1);
      return 0;
    }
  }

  /* Initialize min_length_of_sum */
  min_length_of_sum[0] = 0;
  for (int i = 1; i <= K; i++) min_length_of_sum[i] = N + 1;

	/* The algorithm works by checking all the contiguous subarrays starting from index l.
		 This index moves from 0 to N - 1. We keep an array (say S) of the minimum length of any subarray
		 to the left of this subarray that sums to S[i].
		 As we start the search we have a candidate subarray of length r - l + 1 (r ranges from l to K - 1).
		 We compute its sum, and find the minimum length of a subarray to the left of it that sums to K - sum.
		 If the length of these two subarrays is smaller than current min, it's our new min. If the computed sum
		 is bigger than K we just ignore it (if it's K then S[0] = 0). */

  int min = N + 1, sum, candidate;
  for (int l = 0; l < N; l++)
  {
    /* Recompute the min_lengths to the left of this contiguous subsequence in O(n) time.
			 We just need to consider the new candidate subarrays which are those including the
			 element left of index l. These subarrays are l - 1. */
		sum = 0;
    for (int i = l - 1; i >= 0; i--)
    {
      sum += pop[i];
			if (sum >= K) break;
      candidate = l - i;
      if (min_length_of_sum[sum] > candidate)
        min_length_of_sum[sum] = candidate;
    }

		/* Check every candidate subarray starting at index l, O(n) in time */
		sum = 0;
    for (int r = l; r < N; r++)
    {
      sum += pop[r];
      if (sum > K) break;

      candidate = min_length_of_sum[K - sum] + r - l + 1;
      if (candidate < min) min = candidate;
    }
  }
	/* Complexity: O(N^2) */

  if (min == N + 1) min = -1;
  printf("%i\n", min);
}
