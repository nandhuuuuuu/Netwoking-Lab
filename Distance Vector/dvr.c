#include<stdio.h>
#define INF 999

struct node {
    unsigned dist[20];
    unsigned from[20];
} rt[10];

int main() {
    int costmat[20][20];
    int nodes, i, j, k, count = 0;

    printf("\nDistance Vector Routing");
    printf("\n\nEnter the number of nodes: ");
    scanf("%d", &nodes);

    printf("\nEnter the cost matrix (enter %d for infinity):\n", INF);
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &costmat[i][j]);
            if (costmat[i][j] == 0 && i != j) {
                costmat[i][j] = INF; 
            }
            rt[i].dist[j] = costmat[i][j];
            rt[i].from[j] = j;
        }
    }

    do {
        count = 0;
        for (i = 0; i < nodes; i++) {
            for (j = 0; j < nodes; j++) {
                for (k = 0; k < nodes; k++) {
                    if (rt[i].dist[j] > costmat[i][k] + rt[k].dist[j] && rt[k].dist[j] != INF) {
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    } while (count != 0);

    for (i = 0; i < nodes; i++) {
        printf("\n\nFor router %d:\n", i+1);
        for (j = 0; j < nodes; j++) {
            if (rt[i].dist[j] == INF) {
                printf("\t\nnode %d via %d distance infinity", j + 1, rt[i].from[j] + 1);
            } else {
                printf("\t\nnode %d via %d distance %d", j + 1, rt[i].from[j] + 1, rt[i].dist[j]);
            }
        }
    }

    printf("\n\n");
    return 0;
}