#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#define V 5
#define INF INT_MAX
typedef struct
{
    int vertex;
    int distance;
} Node;
void swap(Node *a, Node *b)
{
    Node temp = *a;
    *a = *b;
    *b = temp;
}
void minHeapify(Node heap[], int size, int index, int pos[])
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < size && heap[left].distance < heap[smallest].distance)
    smallest = left;
    if (right < size && heap[right].distance < heap[smallest].distance)
    smallest = right;
    if (smallest != index)
    {
    pos[heap[smallest].vertex] = index;
    pos[heap[index].vertex] = smallest;
    swap(&heap[smallest], &heap[index]);
    minHeapify(heap, size, smallest, pos);
    }
}
Node extractMin(Node heap[], int *size, int pos[])
{
    Node minNode = heap[0];
    heap[0] = heap[--(*size)];
    pos[heap[0].vertex] = 0;
    minHeapify(heap, *size, 0, pos);
    return minNode;
}
void decreaseKey(Node heap[], int size, int v, int dist, int pos[])
{
    int i = pos[v];
    heap[i].distance = dist;
    while (i > 0 && heap[i].distance < heap[(i - 1) / 2].distance)
    {
        pos[heap[i].vertex] = (i - 1) / 2;
        pos[heap[(i - 1) / 2].vertex] = i;
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
void printPath(int parent[], int j)
{
    if (parent[j] == -1)
    {
        printf("%d ", j);
        return;
    }
    printPath(parent, parent[j]);
    printf("-> %d ", j);
}
void dijkstra(int graph[V][V], int src)
{
    int dist[V], parent[V];
    bool visited[V] = {false};
    int pos[V];
    Node heap[V];
    int size = V;
    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        heap[i].vertex = i;
        heap[i].distance = INF;
        pos[i] = i;
        parent[i] = -1;
    }
    dist[src] = 0;
    heap[src].distance = 0;
    decreaseKey(heap, size, src, 0, pos);
    while (size > 0)
    {
        Node minNode = extractMin(heap, &size, pos);
        int u = minNode.vertex;
        visited[u] = true;
        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] != INF && !visited[v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
                decreaseKey(heap, size, v, dist[v], pos);
            }
        }
    }
    printf("Vertex\t Distance from Source\t Path\n");
    for (int i = 0; i < V; i++)
    {
        printf("%d\t %d\t\t ", i, dist[i]);
        printPath(parent, i);
        printf("\n");
    }
}
int main()
{
    int graph[V][V] = {
    {0, 10, INF, 5, INF},
    {INF, 0, 1, 2, INF},
    {INF, INF, 0, INF, 4},
    {INF, 3, 9, 0, 2},
    {7, INF, 6, INF, 0}};
    dijkstra(graph, 0);
    return 0;
}
