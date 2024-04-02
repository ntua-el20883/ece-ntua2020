#include <stdio.h>

#define Nmax 200000  
#define max(a,b) (((a)>(b))?(a):(b))  
#define min(a,b) (((a)<(b))?(a):(b))  
typedef unsigned int uint;

int SalarySeq[Nmax + 1];                  //Our input
uint m[Nmax + 1];                        //Used for LIS & LDS, see Fotakis' slides.
int LDS_starting_at[Nmax + 1];


/* Binary searches m for the maximum index where comp(val, m[index]) is true */
int BS(uint val, int lo, int hi, bool comp (uint a, uint b));
/* Read input fast */
long readLong();

int main()
{
    /* Read input and initialize m and LDS */
    uint UINT_MAX = ~0;
    int n = readLong();
    uint k = readLong();
    
    SalarySeq[0] = LDS_starting_at[0] = 0;
    m[0] = UINT_MAX;                    //We don't want this changed
    for (int i = 1; i <= n; i++)
    {
        m[i] = LDS_starting_at[i] = 0;
        SalarySeq[i] = readLong();
    }

    /* Get the LDS starting at index i for every index of the array (right to left) */
    int len;
    m[1] = SalarySeq[n], LDS_starting_at[n] = 1;
    for (int i = n - 1; i > 0; i--)
    {
        /* Find the maximum length of a DS which starts at index i */
        len = BS(SalarySeq[i], 0, n - i, [](uint a, uint b) {return a < b;});
        /* m[i] holds the max element which starts a DS of length i */
        m[len] = max(m[len], SalarySeq[i]);
        /* Save the max length of the DS starting at index i */
        LDS_starting_at[i] = len;
    }
    /* Restore m to use now for LIS*/
    m[0] = 0;                               // We don't want this changed
    for (int i = 1; i <= n; i++) m[i] = UINT_MAX;

    /* Moving left to right starting at index 1:
       - Find the longest IS ending at a value where SalarySeq[i] + k could be appended.
         This is done using m array (Fotakis slides).
       
       - Add the length to the length of the LDS starting at index i.
         The result is the longest increasing sequence of the form:
         (m[j] ... m[j + m])  (m[j + m + m'] + k ... m[j + m + m' + m'']  + k).
        
       - Hold the maximum till now.
       - Update the m array used for IS if needed: 
         m[length_of(LIS ending at index i)] > SalarySeq[i]
        (m[i] holds the min element at which a IS of length i ends at).
    */
    int maxl = 0;
    for (int i = 1; i <= n; i++)
    {
        len = BS(SalarySeq[i] + k, 0, i, [](uint a, uint b) {return a > b;});
        maxl = max(maxl, len + LDS_starting_at[i] - 1);

        /*Update m for next indices (no need to check IS greater than len)*/
        len = BS(SalarySeq[i], 0, len, [](uint a, uint b) {return a > b;});
        m[len] = min(m[len], SalarySeq[i]) ;
    }

    printf("%i\n", maxl);
}

int BS(uint val, int lo, int hi, bool comp (uint a, uint b))
{
    int mid = (lo + hi)/2, len = -1;  
    while (lo <= hi)  
    {  
        if (m[mid] >= 0 && comp(val, m[mid]))  
        {  
            lo = mid + 1;  
            len = mid;  
        }  
        else  
            hi = mid - 1;   
        
        mid = (lo + hi)/2;  
    }  
    return len + 1;  
}

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