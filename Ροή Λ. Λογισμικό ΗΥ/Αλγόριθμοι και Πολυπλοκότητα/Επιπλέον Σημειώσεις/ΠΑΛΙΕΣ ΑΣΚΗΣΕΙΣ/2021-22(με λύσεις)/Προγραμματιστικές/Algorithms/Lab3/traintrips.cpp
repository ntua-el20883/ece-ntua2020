#include <cstdio>
#include <climits>
typedef unsigned long long ulong;
typedef unsigned int uint;
#define Nmax 1000
#define dminmax 10000
#define Qmax 100000

/* d[i] = inputs */
ulong d[Nmax];

/* sp[i] = shortest path from 0 to to ~s_i
   reachable[i] = can reach ~s_i from 0 */
ulong sp[dminmax];
bool reachable[dminmax];
bool checked[dminmax];

/* query[i] = i-th query */
uint query[Qmax];

uint find_min(uint dm);
void update(uint d, uint N, uint min_index);
long readLong();

int main()
{
    /* Read input */
    uint N, Q;
    uint dm = UINT_MAX;   // d is gonna be min{d_i}
    N = readLong(); Q = readLong();
    for (uint i = 0; i < N; i++)
    {
        d[i] = readLong();
        dm = dm > d[i] ? d[i] : dm;
    }
    for (uint i = 0; i < Q; i++)
        query[i] = readLong();
    /* ----------------------- */


    /* Dijkstra */
    
    /*All arrays initialized to 0 (default). Do math with -1 */
    sp[0] = reachable[0] = 1;
    uint min_index;
    for (uint dummy = 0; dummy < dm; dummy++)
    {
        /*Find new node to add to SPT according to shortest distance
            from origin (among those not in SPT)*/
        min_index = find_min(dm);
        if(min_index < 0) 
            break;
        
        /* Update shortest paths from origin by considering the new node's edges */
        update(dm, N, min_index);
    }
    /*------------------------------------------------------------*/

    uint node;
    for (uint i = 0; i < Q; i++)
    {
        /*If we can reach a station whos modulo(dm) is the same as the query,
            in the same or less distance than the queried station, we can 
            reach the queried station */
        node = query[i]%dm;
        /*Remember we save the distance + 1 */
        if(sp[node] > 0 && sp[node] - 1 <= query[i])
            printf("YES\n");
        else
            printf("NO\n");
    }
}


/*Finds the node to be added to the SPT, if none to add returns -1 */
uint find_min(uint dm)
{
    ulong min = ULLONG_MAX;
    uint min_index = -1;
    for (uint i = 0; i < dm; i++)
    {
        if(checked[i])
            continue;

        /* sp[i] - 1 = ULONG_MAX when sp[i] = 0 */
        if(reachable[i] && sp[i] - 1 < min)
        {
            min = sp[i];
            min_index = i;
        }
    }
    return min_index;
}

void update(uint dm, uint N, uint min_index)
{
    ulong prev_val, candidate;
    uint get_to;
    for (uint i = 0; i < N; i++)
    {
        get_to = (min_index + d[i])%dm;
        candidate = sp[min_index] + d[i];

        if(!reachable[get_to])
        {
            sp[get_to] = candidate;
            reachable[get_to] = true;
        }

        else
        {
            prev_val = sp[get_to];
            sp[(d[i] + min_index)%dm] = candidate < prev_val ? candidate : prev_val;
        }
    }
    checked[min_index] = true;
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