#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

int main() {
    char v[7];
    int wrong = 0;
    stack_t* st = st_create(sizeof(char));

    for(int i = 0; i < 6; i++) {
        scanf("%s", &v[i]);
    }

    for(int i = 0; i < strlen(v); i++) {
        if(v[i] == '(' || v[i] == '[' || v[i] == '{') {
            st_push(st, &v[i]);
        } else if(st_is_empty(st)) {
            wrong = 1;
            break;
        } else { 
            if((v[i] == ')' && *(char *)st_peek(st) != '(') ||
                (v[i] == ']' && *(char *)st_peek(st) != '[') ||
                (v[i] == '}' && *(char *)st_peek(st) != '{')) {
                    wrong = 1;
                    break;
                }
            st_pop(st);
        }
    } 

    if(!wrong) {
        printf("paranthesis checked\n");
    } else if(!wrong || st_is_empty(st)) {
        printf("Wrong answer\n");
    }

    st_free(st);
    return 0;
}


