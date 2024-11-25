#include <iostream>
#include <vector>

typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
} AdjList;

typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Lista de adjacência do vértice %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

bool isClique(Graph* graph, std::vector<int>& clique) {
    int k = clique.size();
    for (int i = 0; i < k; ++i) {
        for (int j = i + 1; j < k; ++j) {
            AdjListNode* pCrawl = graph->array[clique[i]].head;
            bool edgeExists = false;
            while (pCrawl) {
                if (pCrawl->dest == clique[j]) {
                    edgeExists = true;
                    break;
                }
                pCrawl = pCrawl->next;
            }
            if (!edgeExists) {
                return false;
            }
        }
    }
    return true;
}

bool dfsClique(Graph* graph, int k, int start, std::vector<int>& clique) {
    if (clique.size() == k) {
        return isClique(graph, clique);
    }

    for (int i = start; i < graph->V; ++i) {
        clique.push_back(i);
        if (dfsClique(graph, k, i + 1, clique)) {
            return true;
        }
        clique.pop_back(); // Backtrack
    }
    return false;
}

bool findKClique(Graph* graph, int k) {
    std::vector<int> clique;
    return dfsClique(graph, k, 0, clique);
}

int main() {
    int V = 5;
    Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printGraph(graph);

    int K = 10;
    if (findKClique(graph, K)) {
        printf("Existe um clique de tamanho %d no grafo.\n", K);
    }
    else {
        printf("Não existe um clique de tamanho %d no grafo.\n", K);
    }

    return 0;
}