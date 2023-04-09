#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void free_matrix(int n, int **matrix)
{
	for (int i = 0; i < n; i++)
		free(matrix[i]);

	free(matrix);
}

void alloc_matrix(int n, int m, int ***matrix)
{
    int **a = malloc(n * sizeof(int *));
    DIE(matrix == NULL, "malloc failed");
    *matrix = a;
	for (int i = 0; i < n; i++) {
		a[i] = malloc(m * sizeof(int));
		DIE(a[i] == NULL, "malloc failed");
	}
}

int main ()
{
    int n, m, max = 0, **matrix;
    scanf("%d %d", &n, &m);

    alloc_matrix(n, m, &matrix);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    for(int i = 0; i < n; i++) {
        int cnt = 0, xor_lines = 0;
        while(cnt < m) {
            xor_lines = xor_lines ^ matrix[i][cnt];
            cnt++;

        }
        if(max < xor_lines)
            max = xor_lines;
    }

    for(int i = 0; i < m; i++) {
        int cnt = 0, xor_columns = 0;
        while(cnt < n) {
            xor_columns = xor_columns ^ matrix[cnt][i];
            cnt++;
        }
        if(max< xor_columns)
            max = xor_columns;
    }

    printf("%d", max);

    free_matrix(n,matrix);

    return 0;

}