#include <cstdio>
#include <climits>
#include <tuple>
#include <vector>
#include <algorithm>    
#define Nmax 30000
#define Mmax 200000
#define NN 535000000
using namespace std;
typedef tuple<int, int, int> edge;
long readLong();

edge e[Mmax];
vector<tuple<int, int>> adj[Nmax + 1];    //adj[u] -> neighbours of vertex u
bool visited[Nmax + 1];
int C[NN];
//int C[Nmax + 1][Nmax + 1];
void computeMST(int N, int M);
void dfsBottleneck(int node, int N);
int computeCindex(int, int);


int main()
{
    int N, M, Q;

    N = readLong(); M = readLong();
    int tmp[3];
    for (int i = 0; i < M; i++)
    {
        tmp[0] = readLong(); tmp[1] = readLong(); tmp[2] = readLong();
        e[i] = make_tuple(tmp[0], tmp[1], tmp[2]);
    }

    /* Kruskal (MST == MSBT) O(MlogM) */
    computeMST(N, M);
    /* DFS and precompute O(N^2) */
    for (int i = 1; i <= N; i++)
        if(!visited[i])
            dfsBottleneck(i, N);

    Q = readLong();
    for (int i = 0; i < Q; i++)
    {
        tmp[0] = readLong(); tmp[1] = readLong();
        printf("%d\n", C[computeCindex(tmp[0], tmp[1])]);
    }
} //O(N(N+M) + Q)


class disjointSet
{
    private:
        int elements;
        int *rep, *rank;


    public:
        /* Constructor, makes #elems singleton sets */
        disjointSet(int elems)
        {
            elements = elems;
            rep = new int[elems + 1];
            rank = new int[elems + 1];
            for (int i = 1; i <= elems; i++)
            {
                rep[i] = i;
                rank[i] = 0;
            }
        }

        /* Find and compress path */
        int find(int a)
        {
            if (rep[a] != a) rep[a] = find(rep[a]);
            return rep[a];
        }

        /* Unite by rank */
        void unite(int a, int b)
        {
            int aRep, bRep, aRank, bRank;

            aRep = this->find(a);
            bRep = this->find(b);
            if (aRep == bRep) return;

            aRank = rank[aRep];
            bRank = rank[bRep];

            if (bRank < aRank)
            {
                rep[bRep] = aRep;
                this->find(b);
            }

            else
            {
                rep[aRep] = bRep;
                this->find(a);
            }

            if (aRank == bRank) rank[bRep]++;
        }

        /* Destructor */
        ~disjointSet()
        {
            delete []rank;
            delete []rep;
        }
};

bool compEdge(edge e1, edge e2) { return (get<2>(e1) < get<2>(e2)); }
void computeMST(int N, int M)
{
    sort(e, e + M, compEdge);

    disjointSet mst = disjointSet(N);
    int u1, u2, w;
    for (int i = 0; i < M; i++)
    {
        u1 = get<0>(e[i]); u2 = get<1>(e[i]);
        
        if(mst.find(u1) == mst.find(u2))
            continue;

        w = get<2>(e[i]);
        adj[u1].push_back(make_tuple(u2, w));
        adj[u2].push_back(make_tuple(u1, w));
        mst.unite(u1, u2);
    }
}

int computeCindex(int a, int b)
{
    int i = min(a, b);
    int j = max(a, b);

    return (j*(j - 1))/2 + j - i;
}

void dfsBottleneck(int node, int N)
{
    visited[node] = true;
    int neigh, weight;

    for (auto e: adj[node])
    {
        neigh = get<0>(e);
        if (!visited[neigh])
        {
            weight = get<1>(e);
            for (int i = 1; i <= N; i++)
                if(visited[i])
                {
                    //C[neigh][i] = C[i][neigh] = 
                    //    max(weight, C[node][i]);
                    C[computeCindex(neigh, i)] = 
                        max(weight, C[computeCindex(node, i)]);
                }
            dfsBottleneck(neigh, N);
        }
    }
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