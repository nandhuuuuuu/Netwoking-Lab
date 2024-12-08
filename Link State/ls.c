#include <stdio.h>
#include <limits.h>

int main() {
    int H, i, j, adj[50][50], d;

    printf("LINK STATE ROUTING PROTOCOL:\nEnter the number of hops: ");
    scanf("%d", &H);
  
    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < H; i++)
        for (j = 0; j < H; j++)
            scanf("%d", &adj[i][j]);

    int dist[H], visited[H], round, v;

    for (i = 0; i < H; i++) { 
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[0] = 0; 

    for (round = 0; round < H - 1; round++) {
        int min = INT_MAX, min_index;

        for (v = 0; v < H; v++) {
            if (visited[v] == 0 && dist[v] < min) { 
                min = dist[v];
                min_index = v;
            }
        }

        visited[min_index] = 1;

        for (d = 0; d < H; d++) {
            if (!visited[d] && adj[min_index][d] && dist[min_index] != INT_MAX && dist[min_index] + adj[min_index][d] < dist[d]) {
                dist[d] = dist[min_index] + adj[min_index][d]; 
            }
        }
    }

    printf("Vertex\tDistance from Source\n");
    for (i = 0; i < H; i++) {
        printf("%d\t\t%d\n", i, dist[i]);
    }

    return 0;
}
