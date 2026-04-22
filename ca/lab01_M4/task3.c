#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);

    int **a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        a[i] = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);

    int **t = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
        t[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            t[j][i] = a[i][j];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", t[i][j]);
        printf("\n");
    }

    for (int i = 0; i < n; i++) free(a[i]);
    free(a);
    for (int i = 0; i < m; i++) free(t[i]);
    free(t);

    return 0;
}
