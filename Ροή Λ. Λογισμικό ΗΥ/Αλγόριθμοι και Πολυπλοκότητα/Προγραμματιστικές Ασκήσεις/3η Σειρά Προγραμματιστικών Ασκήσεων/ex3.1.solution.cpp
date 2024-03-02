#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

#define max_nmk 300000
#define inf 2000000000

long long int N;
long long int M;
long long int K;

struct Edge {
    long long int src, dest, time;
};

struct Edge mst[max_nmk];

struct Graph {
    struct Edge* edge;
    long long int numEdges;
};

struct Graph* createGraph(long long int m) {

    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));

    graph->edge = (struct Edge*) malloc(m * sizeof(struct Edge));
    graph->numEdges = 0;

    return graph;
}

struct subset {
    long long int rank;
    long long int parent;
};

long long int find(struct subset subsets[], long long int i) {

    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Union(struct subset subsets[], long long int x, long long int y) {
    long long int xroot = find(subsets, x);
    long long int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;

    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int descendingTime(const void* a, const void* b) {

    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;

    if (a1->time > b1->time)
        return -1;

    if (a1->time < b1->time)
        return +1;

    return 0;
}

void KruskalMST(struct Graph* graph) {

    long long int e = 0;
    long long int i = 0;
    long long int v;

    qsort(graph->edge, M, sizeof(graph->edge[0]), descendingTime);

    struct subset *subsets = (struct subset*) malloc( N * sizeof(struct subset) );

    for (v = 0; v < N; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < N - 1) {
        struct Edge next_edge = graph->edge[i++];

        long long int x = find(subsets, next_edge.src);
        long long int y = find(subsets, next_edge.dest);

        if (x != y) {
            mst[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
}

long long int max(long long int a, long long int b) {
    return (a > b) ? a : b;
}

int main(int argc, char *argv[]) {
    long long int i, cityA, cityB, t;

    if(scanf("%lld %lld %lld", &N, &M, &K) != 3) {
        cout << "\nError while reading file.\n";
        exit(1);
    }

    if (K >= M) {
        cout << "infinity\n";
        return 0;
    }

    struct Graph* graph = createGraph(max(M, N-1)+N);
    long long int cc = N;

    struct subset *connectedComponents = (struct subset*) malloc(N * sizeof(struct subset));

    for (i = 0; i < N; ++i) {
        connectedComponents[i].parent = i;
        connectedComponents[i].rank = 0;
    }

    int rootsCC[N];
    for (i = 0; i < N; i++)
        rootsCC[i] = 0;

    long long int root1, root2, last, j;

    for (i = 0; i < M; i++) {
        scanf("%lld %lld %lld", &cityA, &cityB, &t);
        graph->edge[i].src = cityA-1;
        graph->edge[i].dest = cityB-1;
        graph->edge[i].time = t;

        graph->numEdges += 1;

        root1 = find(connectedComponents, cityA-1);
        root2 = find(connectedComponents, cityB-1);

        if (root1 != root2) {
            cc--;
            Union(connectedComponents, cityA-1, cityB-1);

            if (root1 != find(connectedComponents, cityA-1)) {
                rootsCC[root1] = 1;
            }

            else {
                rootsCC[root2] = 1;
            }
        }
    }

    if (cc > 1) {

        i = 0;

        while (i < N) {
            if (rootsCC[i] == 0) {
                last = i++;
                break;
            }
            i++;
        }

        while (i < N) {
            if (rootsCC[i] == 0) {
                rootsCC[last] = 1;
                graph->edge[graph->numEdges].src = last;
                graph->edge[graph->numEdges].dest = i;
                graph->edge[graph->numEdges].time = inf;

                graph->numEdges += 1;

                last = i;
            }
            i++;
        }
    }

    KruskalMST(graph);

    cout << mst[(N-1)-cc-K].time<<endl;

    return 0;
}
