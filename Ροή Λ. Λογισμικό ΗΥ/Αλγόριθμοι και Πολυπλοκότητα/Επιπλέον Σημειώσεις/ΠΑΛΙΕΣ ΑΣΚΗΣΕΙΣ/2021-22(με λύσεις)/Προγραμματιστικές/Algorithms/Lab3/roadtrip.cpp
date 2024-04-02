#include <cstdio>
#include <climits>
#include <tuple>
#include <vector>
#include <algorithm>    
#define Nmax 30000
#define Mmax 200000
#define LEVELmax 15 //log_2(30,000) = 14.87..
using namespace std;
typedef tuple<int, int, int> edge;
long readLong();

edge e[Mmax];
vector<tuple<int, int>> adj[Nmax + 1];    //adj[u] -> neighbours of vertex u
int depth[Nmax + 1];
int ancest[Nmax + 1][LEVELmax];
int maxe[Nmax + 1][LEVELmax];
bool visited[Nmax + 1];
void computeMST(int N, int M);
void dfs(int, int, int);
int lcaBottleneck(int, int);
void computeSparse(int);


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
            dfs(i, 0, 0);
    /* Precompute ancest and maxe */
    computeSparse(N);

    Q = readLong();
    for (int i = 0; i < Q; i++)
    {
        tmp[0] = readLong(); tmp[1] = readLong();
        printf("%d\n", lcaBottleneck(tmp[0], tmp[1]));
    }
}  //O((N + M + Q)logN)


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
    int u1, u2, w, count = 0;
    for (int i = 0; i < M; i++)
    {
        u1 = get<0>(e[i]); u2 = get<1>(e[i]);
        
        if(mst.find(u1) == mst.find(u2))
            continue;

        w = get<2>(e[i]);
        adj[u1].push_back(make_tuple(u2, w));
        adj[u2].push_back(make_tuple(u1, w));
        mst.unite(u1, u2);
        count++;
        if(count == N - 1) break;
    }
}

/* DFS along the forest, while computing the parents of nodes
    parent(i) = ancest(i, 0) */
void dfs(int node, int prev, int weight)
{
    visited[node] = true;
    depth[node] = depth[prev] + 1;
    ancest[node][0] = prev;
    maxe[node][0] = weight;
    int neigh;

    for (auto e: adj[node])
    {
        neigh = get<0>(e);
        if (!visited[neigh])
        {
            weight = get<1>(e);
            dfs(neigh, node, weight);
        }
    }
}//O(2*n)=O(n)

/* Compute the sparse tables ancest(i, j), maxe(i, j) where: 
    ancest(i, j) := ancestor of i, 2^j levels above it
    maxe(i, j) := bottleneck along the path connecting i and ancest(i, j) */
void computeSparse(int n)
{
    for (int i = 1; i < LEVELmax; i++)
    {
        for (int node = 1; node <= n; node++)
        {
            if (ancest[node][i - 1] != 0)
            {
                ancest[node][i] =
                    ancest[ancest[node][i - 1]][i - 1];
            
                maxe[node][i] = max(maxe[node][i - 1], 
                            maxe[ ancest[node][i - 1] ][i - 1]);
            }
        }
    }
}//O(nlogn)

int lcaBottleneck(int u, int v)
{
    if (depth[v] < depth[u])
        swap(u, v);
 
    int diff = depth[v] - depth[u];
    int e = 0;
 
    
    /* "Bring" v to the same level as u 
        and compute the bottleneck along the way*/
    for (int i = LEVELmax - 1; 
       i >= 0 && diff > 0; i--)
    {
        if ((1 << i) <= diff)
        {
            e = max(e, maxe[v][i]);
            v = ancest[v][i];
            diff -= (1 << i);
        }
            
    }
 

    /* Now depth[u] == depth[v]. If u is the parent of v we're done */
    if (u == v)
        return e;
 
    
    /* Find the LCA (actually stop at the level just below the LCA)
        and compute the bottlenecks along the way */
    for (int i = LEVELmax - 1; i >= 0; i--)
        if (ancest[u][i] != ancest[v][i])
        {
            e = max(e, max(maxe[u][i], maxe[v][i]));
            u = ancest[u][i];
            v = ancest[v][i];
        }

    /* Consider the edge(s) connecting that level to the LCA */
    return max(e, max(maxe[u][0], maxe[v][0]));
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