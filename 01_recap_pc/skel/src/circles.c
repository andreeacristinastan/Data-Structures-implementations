#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
typedef struct circle {
    int *r;
    int *x;
    int *y;

} circle;

int main()
{
    int n, cnt = 0, i = 0, j = 0;
    int *int_r, *int_x, *int_y;
    circle *v;
    scanf("%d", &n);
    v = malloc(sizeof(circle));

    v->r = malloc(n*sizeof(int));
    v->x = malloc(n*sizeof(int));
    v->y = malloc(n*sizeof(int));

    int_r = v->r;
    int_x = v->x;
    int_y = v->y;

    for(i = 0; i < n; i++) {
        scanf("%d%d%d", &int_x[i], &int_y[i], &int_r[i]);
    }

    for(i = 0; i<n; i++) {
        for(j = i+1; j < n; j++) {
            int c1c2 =  (int_x[i] - int_x[j])*(int_x[i] - int_x[j]) + (int_y[i]-int_y[j])*(int_y[i]-int_y[j]);
            int r1r2 = (int_r[i] + int_r[j])*(int_r[i] + int_r[j]);
            if(c1c2 <= r1r2)
                cnt++;
        }
    }

    printf("%d",cnt);
    
    free(v->r);
    free(v->x);
    free(v->y);
    free(v);

    return 0;
}
