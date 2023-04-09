#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"

#define MAX_STRING_SIZE		256

struct recipe {
    char name[MAX_STRING_SIZE];
    char* ingredients[40];
    int cnt;
};

struct ingredients {
    char* name_i[40];
    char ingredients_i[MAX_STRING_SIZE];
    int cnt_i;
};

static void
print_recipe(struct recipe *p_info)
{
	if (p_info == NULL) {
		printf("Reteta inexistenta!\n");
		return;
	}
	printf("* %s: ", p_info->name);
    for(int i = 0; i < p_info->cnt; i++) {
	    printf("%s | ", p_info->ingredients[i]);
    }
        printf("\n");

}

static void
print_ingredients(struct ingredients *p_info_ingredients) {
    if (p_info_ingredients == NULL) {
		printf("Reteta inexistenta!\n");
		return;
	}
	printf("* %s: ", p_info_ingredients->ingredients_i);
    for(int i = 0; i < p_info_ingredients->cnt_i; i++) {
	    printf("%s ", p_info_ingredients->name_i[i]);
    }
    printf("\n");
}

int
main()
{
	hashtable_t *ht_recipe, *ht_ingredients;
	struct recipe retete[100];
	struct recipe *p_info;
    struct ingredients ingrediente[100];
    struct ingredients *p_info_ingredients;
	int current_key;

    strcpy(retete[0].name, "Bomboane cu lapte");
	retete[0].ingredients[0] = "apa";
    retete[0].ingredients[1] = "zahar";
    retete[0].ingredients[2] = "smantana";
    retete[0].cnt = 3;

    strcpy(retete[1].name, "Chec");
	retete[1].ingredients[0] = "oua";
    retete[1].ingredients[1] = "faina";
    retete[1].ingredients[2] = "zahar";
    retete[1].ingredients[3] = "unt";
    retete[1].ingredients[4] = "lapte";
    retete[1].ingredients[5] = "cacao";
    retete[1].cnt = 6;

    strcpy(retete[2].name, "Mamaliga");
	retete[2].ingredients[0] = "apa";
    retete[2].ingredients[1] = "sare";
    retete[2].ingredients[2] = "malai";
    retete[2].cnt = 3;

    strcpy(retete[3].name, "MBS");
	retete[3].ingredients[0] = "apa";
    retete[3].ingredients[1] = "sare";
    retete[3].ingredients[2] = "malai";
    retete[3].ingredients[3] = "branza";
    retete[3].ingredients[4] = "smantana";
    retete[3].cnt = 5;

    strcpy(retete[4].name, "Bruschete");
	retete[4].ingredients[0] = "rosii";
    retete[4].ingredients[1] = "usturoi";
    retete[4].ingredients[2] = "busuioc";
    retete[4].ingredients[3] = "ulei de masline";
    retete[4].ingredients[4] = "ceapa";
    retete[4].ingredients[5] = "sare";
    retete[4].ingredients[6] = "bagheta";
    retete[4].cnt = 7;

    ht_recipe = ht_create(5, hash_function_string,
				compare_function_strings);
    //a

    ht_put(ht_recipe, "Bomboane cu lapte", strlen("Bomboane cu lapte") + 1, &retete[0],
		    sizeof(retete[0]));
	p_info = ht_get(ht_recipe, "Bomboane cu lapte");
    print_recipe(p_info);

    ht_put(ht_recipe, "Chec", strlen("Chec") + 1, &retete[1],
		    sizeof(retete[1]));
	p_info = ht_get(ht_recipe, "Chec");
    print_recipe(p_info);

    ht_put(ht_recipe, "Mamaliga", strlen("Mamaliga") + 1, &retete[2],
		    sizeof(retete[2]));
	p_info = ht_get(ht_recipe, "Mamaliga");
    print_recipe(p_info);

    ht_put(ht_recipe, "MBS", strlen("MBS") + 1, &retete[3],
		    sizeof(retete[3]));
	p_info = ht_get(ht_recipe, "MBS");
    print_recipe(p_info);

    ht_put(ht_recipe, "Bruschete", strlen("Bruschete") + 1, &retete[4],
		    sizeof(retete[4]));
	p_info = ht_get(ht_recipe, "Bruschete");
    print_recipe(p_info);

    //b
    for(int i = 0; i < ht_recipe->size; i++) {
        if(ht_has_key(ht_recipe, "Ciorba") == 1) {
            printf("%s\n", p_info->ingredients[i]);
        }else {
            printf("I don’t know how to cook this\n");
        }
    }
    for(int i = 0; i < ht_recipe->size; i++) {
        if(ht_has_key(ht_recipe, "Bruschete") == 1) {
            printf("%s ", p_info->ingredients[i]);
        } else 
            printf("I don’t know how to cook this\n");
    }
    
    //d
    for(int i = 0; i < ht_recipe->hmax; i++) {
        ll_node_t* current = ht_recipe->buckets[i]->head;

        while(current) {
            ll_node_t* next_node = current->next;
            if(retete[i].cnt > 5) {
                ht_remove_entry(ht_recipe, p_info->ingredients[i]);
            }
            current = next_node;
        }
    }

    ht_free(ht_recipe);


    //c
    printf("\n\n");
	strcpy(ingrediente[0].ingredients_i, "apa");
    ingrediente[0].name_i[0] = "Bomboane cu lapte";
    ingrediente[0].name_i[1] = "MBS";
    ingrediente[0].cnt_i = 2;

    strcpy(ingrediente[1].ingredients_i, "zahar");
    ingrediente[1].name_i[0] = "Bomboane cu lapte";
    ingrediente[1].name_i[1] = "Chec";
    ingrediente[1].cnt_i = 2;

    strcpy(ingrediente[2].ingredients_i, "smantana");
    ingrediente[2].name_i[0] = "Bomboane cu lapte";
    ingrediente[2].name_i[1] = "MBS";
    ingrediente[2].cnt_i = 2;
    
	strcpy(ingrediente[3].ingredients_i, "oua");
    ingrediente[3].name_i[0] = "Chec";
    ingrediente[3].cnt_i = 1;

    strcpy(ingrediente[4].ingredients_i, "faina");
    ingrediente[4].name_i[0] = "Chec";
    ingrediente[4].cnt_i = 1;

    strcpy(ingrediente[5].ingredients_i, "unt");
    ingrediente[5].name_i[0] = "Chec";
    ingrediente[5].cnt_i = 1;

    strcpy(ingrediente[6].ingredients_i, "lapte");
    ingrediente[6].name_i[0] = "Chec";
    ingrediente[6].cnt_i = 1;
    
    strcpy(ingrediente[7].ingredients_i, "cacao");
    ingrediente[7].name_i[0] = "Chec";
    ingrediente[7].cnt_i = 1;

	strcpy(ingrediente[8].ingredients_i, "sare");
    ingrediente[8].name_i[0] = "Mamaliga";
    ingrediente[8].name_i[1] = "MBS";
    ingrediente[8].name_i[2] = "Bruschete";
    ingrediente[8].cnt_i = 3;
    
    strcpy(ingrediente[9].ingredients_i, "malai");
    ingrediente[9].name_i[0] = "Mamaliga";
    ingrediente[9].name_i[1] = "MBS";
    ingrediente[9].cnt_i = 2;

	strcpy(ingrediente[10].ingredients_i, "branza");
    ingrediente[10].name_i[0] = "MBS";
    ingrediente[10].cnt_i = 1;

	strcpy(ingrediente[11].ingredients_i, "rosii");
    ingrediente[11].name_i[0] = "Bruschete";
    ingrediente[11].cnt_i = 1;

    strcpy(ingrediente[12].ingredients_i, "usturoi");
    ingrediente[12].name_i[0] = "Bruschete";
    ingrediente[12].cnt_i = 1;

    strcpy(ingrediente[13].ingredients_i, "busuioc");
    ingrediente[13].name_i[0] = "Bruschete";
    ingrediente[13].cnt_i = 1;

    strcpy(ingrediente[14].ingredients_i, "ulei de masline");
    ingrediente[14].name_i[0] = "Bruschete";
    ingrediente[14].cnt_i = 1;

    strcpy(ingrediente[15].ingredients_i, "ceapa");
    ingrediente[15].name_i[0] = "Bruschete";
    ingrediente[15].cnt_i = 1;

    strcpy(ingrediente[16].ingredients_i, "bagheta");
    ingrediente[16].name_i[0] = "Bruschete";
    ingrediente[16].cnt_i = 1;

    ht_ingredients = ht_create(20, hash_function_string,
				compare_function_strings);
    
    ht_put(ht_ingredients, "apa", strlen("apa") + 1, &ingrediente[0],
		    sizeof(ingrediente[0]));
	p_info_ingredients = ht_get(ht_ingredients, "apa");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "zahar", strlen("zahar") + 1, &ingrediente[1],
		    sizeof(ingrediente[1]));
	p_info_ingredients = ht_get(ht_ingredients, "zahar");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "smantana", strlen("smantana") + 1, &ingrediente[2],
		    sizeof(ingrediente[2]));
	p_info_ingredients = ht_get(ht_ingredients, "smantana");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "oua", strlen("oua") + 1, &ingrediente[3],
		    sizeof(ingrediente[3]));
	p_info_ingredients = ht_get(ht_ingredients, "oua");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "faina", strlen("faina") + 1, &ingrediente[4],
		    sizeof(ingrediente[4]));
	p_info_ingredients = ht_get(ht_ingredients, "faina");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "unt", strlen("unt") + 1, &ingrediente[5],
		    sizeof(ingrediente[5]));
	p_info_ingredients = ht_get(ht_ingredients, "unt");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "lapte", strlen("lapte") + 1, &ingrediente[6],
		    sizeof(ingrediente[6]));
	p_info_ingredients = ht_get(ht_ingredients, "lapte");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "cacao", strlen("cacao") + 1, &ingrediente[7],
		    sizeof(ingrediente[7]));
	p_info_ingredients = ht_get(ht_ingredients, "cacao");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "sare", strlen("sare") + 1, &ingrediente[8],
		    sizeof(retete[8]));
	p_info_ingredients = ht_get(ht_ingredients, "sare");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "malai", strlen("malai") + 1, &ingrediente[9],
		    sizeof(ingrediente[9]));
	p_info_ingredients = ht_get(ht_ingredients, "malai");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "branza", strlen("branza") + 1, &ingrediente[10],
		    sizeof(ingrediente[10]));
	p_info_ingredients = ht_get(ht_ingredients, "branza");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "rosii", strlen("rosii") + 1, &ingrediente[11],
		    sizeof(ingrediente[11]));
	p_info_ingredients = ht_get(ht_ingredients, "rosii");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "usturoi", strlen("usturoi") + 1, &ingrediente[12],
		    sizeof(ingrediente[12]));
	p_info_ingredients = ht_get(ht_ingredients, "usturoi");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "busuioc", strlen("busuioc") + 1, &ingrediente[13],
		    sizeof(ingrediente[13]));
	p_info_ingredients = ht_get(ht_ingredients, "busuioc");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "ulei de masline", strlen("ulei de masline") + 1, &ingrediente[14],
		    sizeof(ingrediente[14]));
	p_info_ingredients = ht_get(ht_ingredients, "ulei de masline");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "ceapa", strlen("ceapa") + 1, &ingrediente[15],
		    sizeof(ingrediente[15]));
	p_info_ingredients = ht_get(ht_ingredients, "ceapa");
    print_ingredients(p_info_ingredients);

    ht_put(ht_ingredients, "bagheta", strlen("bagheta") + 1, &ingrediente[16],
		    sizeof(ingrediente[16]));
	p_info_ingredients = ht_get(ht_ingredients, "bagheta");
    print_ingredients(p_info_ingredients);
    
    int cnt = 0;

   for(int i = 0; i < 17; i++) {
        if(strcmp(ingrediente[i].ingredients_i,"sare") == 0) {
            while(ingrediente[i].cnt_i != 0) {
                printf("%s ", ingrediente[i].name_i[cnt]);
                cnt++;
                ingrediente[i].cnt_i--;
            }
        }
    }

    ht_free(ht_ingredients);

    return 0;
}