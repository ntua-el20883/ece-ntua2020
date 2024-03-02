#include <iostream>
#include <limits.h>
#include <cstdlib>

using namespace std;

struct Node {
    int dest, weight;
    char valid;
    Node* next;
};

struct AdjList {
    Node* head;
};

struct Graph {
    int V;
    AdjList* array;
};

struct MinHeapNode {
    int v;
    long long dist;
};

struct MinHeap {
    int size, capacity, *pos;
    MinHeapNode **array;
};

Node* CreateNewNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->valid = 0;
    newNode->next = nullptr;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = nullptr;

    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = CreateNewNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = CreateNewNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

MinHeapNode* newMinHeapNode(int v, long long dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return nullptr;

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap* minHeap, int v, long long dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

char isInMinHeap(MinHeap* minHeap, int v) {
    return minHeap->pos[v] < minHeap->size;
}

long long* H;

long long dijkstra(Graph* graph, int src, int dest, int offset) {
    int V = graph->V, v;
    long long dist[V], res = 0, k;
    MinHeap* minHeap = createMinHeap(V);

    for (v = 0; v < V; ++v) {
        dist[v] = LLONG_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = offset;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        if (u == dest) {
            res = minHeapNode->dist;
            break;
        }

        Node* pCrawl = graph->array[u].head;
        while (pCrawl != nullptr) {
            int v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && dist[u] != LLONG_MAX) {
                if (pCrawl->valid == 0) {
                    if (pCrawl->weight + dist[u] < dist[v]) {
                        dist[v] = dist[u] + pCrawl->weight;
                        decreaseKey(minHeap, v, dist[v]);
                    }
                }
                else {
                    if (H[u] <= dist[u] && dist[u] < H[v])
                        k = H[v];
                    else if (H[v] <= dist[u] && dist[u] < H[u])
                        k = H[u];
                    else
                        k = dist[u];
                    if (pCrawl->weight + k < dist[v]) {
                        dist[v] = pCrawl->weight + k;
                        decreaseKey(minHeap, v, dist[v]);
                    }
                }
            }
            pCrawl = pCrawl->next;
        }
    }
    return res;
}

struct TourNode {
    int v;
    TourNode* next;
};

int main() {
    int N, M, K;
    long long res;
    int T, A, B, i, u, v, c;

    Graph* G;
    Node* temp2;
    TourNode* head, * curr, * t;

    cin >> N >> M;
    cin >> A >> B >> T >> K;

    H = (long long*)malloc(N * sizeof(long long));
    head = (TourNode*)malloc(sizeof(TourNode));

    cin >> c;

    head->v = c - 1;
    head->next = nullptr;
    curr = head;

    for (i = 1; i < K; i++) {
        cin >> c;
        t = (TourNode*)malloc(sizeof(TourNode));
        t->v = c - 1;
        t->next = nullptr;
        curr->next = t;
        curr = t;
    }
    G = createGraph(N);

    for (i = 0; i < M; i++) {
        cin >> u >> v >> c;
        addEdge(G, u - 1, v - 1, c);
    }
    H[head->v] = 0;

    for (curr = head->next, t = head; curr != nullptr; curr = curr->next, t = t->next) {
        for (temp2 = G->array[t->v].head; temp2 != nullptr; temp2 = temp2->next)
            if (temp2->dest == curr->v) {
                temp2->valid = 1;
                H[curr->v] = H[t->v] + temp2->weight;
                break;
            }

        for (temp2 = G->array[curr->v].head; temp2 != nullptr; temp2 = temp2->next)
            if (temp2->dest == t->v) {
                temp2->valid = 1;
                break;
            }
    }
    res = dijkstra(G, A - 1, B - 1, T);
    cout << res - T << endl;
    return 0;
}
