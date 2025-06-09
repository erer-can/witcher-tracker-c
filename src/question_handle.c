#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

void handle_specific_ingredient_query(char words[][MAX_WORD_LEN], int word_count)
{
    /**
        * Function Name: handle_specific_ingredient_query
        *
        * Purpose:
        *    Handles the query for a specific ingredient and prints its quantity.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int word_count - The number of words in the input line.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Prints the quantity of the specified ingredient.
        *     - If the ingredient is not found, prints 0.
     */
    char ingredient_name[MAX_WORD_LEN];
    strcpy(ingredient_name, words[2]);
    int quantity = 0;

    for (int i = 0; i <= last_added_ingredient_index; i++)
    {
        if (strcmp(ingredients[i].name, ingredient_name) == 0)
        {
            quantity = ingredients[i].quantity;
            break;
        }
    }

    printf("%d", quantity);
    printf("\n");
}

void handle_specific_potion_query(char words[][MAX_WORD_LEN], int word_count, char const *line)
{
    /**
        * Function Name: handle_specific_potion_query
        *
        * Purpose:
        *    Handles the query for a specific potion and prints its quantity.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int word_count - The number of words in the input line.
        *     const char *line - The original input line.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Prints the quantity of the specified potion.
        *     - If the potion is not found, prints 0.
        *     - If the potion name is invalid, prints "INVALID".
     */
    char potion_name[MAX_LINE_LENGTH] = "";

    for (int i = 2; i < word_count; i++)
    {
        if (strcmp(words[i], "?") == 0)
            break;
        strcat(potion_name, words[i]);
        if (i < word_count - 2)
        {
            strcat(potion_name, " ");
        }
    }
    //we first construct the potion name and check if there is multiple spaces between words
    //if not valid we print INVALID and stop
    //else we get the quantity of the potion
    if (!is_valid_potion_name_spacing(line, potion_name))
    {
        printf("INVALID\n");
        return;
    }

    int quantity = 0;

    for (int i = 0; i <= last_added_potion_index; i++)
    {
        if (strcmp(potions[i].name, potion_name) == 0)
        {
            quantity = potions[i].quantity;
            break;
        }
    }

    printf("%d", quantity);
    printf("\n");
}

void handle_specific_trophy_query(char words[][MAX_WORD_LEN], int word_count)
{
    /**
        * Function Name: handle_specific_trophy_query
        *
        * Purpose:
        *    Handles the query for a specific trophy and prints its quantity.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int word_count - The number of words in the input line.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Prints the quantity of the specified trophy.
        *     - If the trophy is not found, prints 0.
     */
    char trophy_name[MAX_WORD_LEN];
    strcpy(trophy_name, words[2]);
    int quantity = 0;

    for (int i = 0; i <= last_added_trophy_index; i++)
    {
        if (strcmp(trophies[i].name, trophy_name) == 0)
        {
            quantity = trophies[i].quantity;
            break;
        }
    }

    printf("%d", quantity);
    printf("\n");
}

void handle_all_ingredients_query()
{
    /**
        * Function Name: handle_all_ingredients_query
        *
        * Purpose:
        *    Handles the query for all ingredients and prints their quantities.
        *
        * Parameters:
        *     void - This function does not take any parameters.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Prints the quantities of all ingredients in alphabetical order.
        *     - If no ingredients are found, prints "None".
     */
    if (last_added_ingredient_index == -1)
    {
        printf("None\n");
        return;
    }

    //since we need the ingredients in alpahabetical order we sort them using our custom ingredient comparator
    //we use qsort to sort the ingredients array
    //and print them with their quantities in the necessary format
    qsort(ingredients, last_added_ingredient_index + 1, sizeof(Ingredient), cmpIngredient);

    for (int i = 0; i <= last_added_ingredient_index; i++)
    {
        if (ingredients[i].quantity == 0)
            continue;
        printf("%d %s", ingredients[i].quantity, ingredients[i].name);
        if (i < last_added_ingredient_index)
        {
            printf(", ");
        }
    }
    printf("\n");
}

void handle_all_potions_query()
{
    /**
        * Function Name: handle_all_potions_query
        *
        * Purpose:
        *    Handles the query for all potions and prints their quantities.
        *
        * Parameters:
        *     void - This function does not take any parameters.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Prints the quantities of all potions in alphabetical order.
        *     - If no potions are found, prints "None".
     */
    if (last_added_potion_index == -1)
    {
        printf("None\n");
        return;
    }
    //since we need the potions in alpahabetical order we sort them using our custom potion comparator
    //we use qsort to sort the potions array
    //and print them with their quantities in the necessary format
    //we don't do potion name check here because if the potion is already stored then its name was valid when the input was taken
    qsort(potions, last_added_potion_index + 1, sizeof(Potion), cmpPotion);

    for (int i = 0; i <= last_added_potion_index; i++)
    {
        if (potions[i].quantity == 0)
            continue;
        printf("%d %s", potions[i].quantity, potions[i].name);
        if (i < last_added_potion_index)
        {
            printf(", ");
        }
    }
    printf("\n");
}

void handle_all_trophies_query()
{
    /**
        * Function Name: handle_all_trophies_query
        *
        * Purpose:
        *    Handles the query for all trophies and prints their quantities.
        *
        * Parameters:
        *     void - This function does not take any parameters.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Prints the quantities of all trophies in alphabetical order.
        *     - If no trophies are found, prints "None".
     */
    if (last_added_trophy_index == -1)
    {
        printf("None\n");
        return;
    }

    //since we need the trophies in alpahabetical order we sort them using our custom trophy comparator
    //we use qsort to sort the trophies array
    //and print them with their quantities in the necessary format
    qsort(trophies, last_added_trophy_index + 1, sizeof(Trophy), cmpTrophy);

    for (int i = 0; i <= last_added_trophy_index; i++)
    {
        if (trophies[i].quantity == 0)
            continue;
        printf("%d %s", trophies[i].quantity, trophies[i].name);
        if (i < last_added_trophy_index)
        {
            printf(", ");
        }
    }
    printf("\n");
}

void handle_monster_query(char words[][MAX_WORD_LEN], int word_count)
{
    /**
        * Function Name: handle_monster_query
        *
        * Purpose:
        *    Handles the query for a specific monster and prints the signs and potions that can be used against it.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int word_count - The number of words in the input line.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Prints the signs and potions of the specified monster in alphabetical order.
        *     - If the monster is not found, prints "No knowledge of <monster_name>".
     */
    char monster_name[MAX_WORD_LEN];
    strcpy(monster_name, words[4]);

    for (int i = 0; i <= last_added_monster_index; i++)
    {
        //we traverse the array to find the monster
        if (strcmp(monsters[i].name, monster_name) == 0)
        {
            //when we find it we create an array to store the signs and potions effective against it
            //and compare it using our custom string comparator to print in alphabetical order
            //we use a string comparator because no quantity exists and we only handle the names of potions and signs
            int cnt = 0;
            int total = monsters[i].sign_count + monsters[i].potion_count;
            char **signs_potions = malloc(total * sizeof(char *));
            for (int k = 0; k < total; k++)
                signs_potions[k] = malloc(MAX_WORD_LEN);

            for (int j = 0; j < monsters[i].sign_count; j++)
            {
                strcpy(signs_potions[cnt], monsters[i].signs[j].name);
                cnt++;
            }
            for (int j = 0; j < monsters[i].potion_count; j++)
            {
                strcpy(signs_potions[cnt], monsters[i].potions[j].name);
                cnt++;
            }

            qsort(signs_potions, cnt, sizeof(char *), cmp);

            for (int j = 0; j < cnt; j++)
            {
                printf("%s", signs_potions[j]);
                if (j < cnt - 1)
                {
                    printf(", ");
                }
                free(signs_potions[j]);
            }
            free(signs_potions);
            printf("\n");
            return;
        }
    }
    printf("No knowledge of %s\n", monster_name);
}

void handle_potion_recipe_query(char words[][MAX_WORD_LEN], int word_count, const char *line)
{
    /**
        * Function Name: handle_potion_recipe_query
        *
        * Purpose:
        *    Handles the query for a potion recipe and prints the ingredients required to brew it.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int word_count - The number of words in the input line.
        *     const char *line - The original input line.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Prints the ingredients required to brew the specified potion in decreasing quantity order.
        *     - If the potion is not found, prints "No formula for <potion_name>".
        *     - If the potion name is invalid, prints "INVALID".
     */
    char potion_name[MAX_LINE_LENGTH] = "";

    for (int i = 3; i < word_count - 1; i++)
    {
        strcat(potion_name, words[i]);
        if (i < word_count - 2)
        {
            strcat(potion_name, " ");
        }
    }

    if (!is_valid_potion_name_spacing(line, potion_name))
    {
        printf("INVALID\n");
        return;
    }

    for (int i = 0; i <= last_added_formula_index; i++)
    {
        //we traverse the array to find the potion
        //when we find it we create an array to store the ingredients
        //and compare it using our custom recipe comparator to print in decreasing quantity order, if same in alphabetical order
        if (strcmp(formulas[i].name, potion_name) == 0)
        {
            if (formulas[i].ingredient_count == 0)
            {
                printf("No formula for %s\n", potion_name);
                return;
            }

            Ingredient *ingredients_in_formula = malloc(formulas[i].ingredient_count * sizeof(Ingredient));
            for (int j = 0; j < formulas[i].ingredient_count; j++)
            {
                strcpy(ingredients_in_formula[j].name, formulas[i].ingredients[j].name);
                ingredients_in_formula[j].quantity = formulas[i].ingredients[j].quantity;
            }

            qsort(ingredients_in_formula, formulas[i].ingredient_count, sizeof(Ingredient), cmpForRecipe);

            for (int j = 0; j < formulas[i].ingredient_count; j++)
            {
                printf("%d %s", ingredients_in_formula[j].quantity, ingredients_in_formula[j].name);
                if (j < formulas[i].ingredient_count - 1)
                {
                    printf(", ");
                }
            }
            free(ingredients_in_formula);
            printf("\n");
            return;
        }
    }
    printf("No formula for %s\n", potion_name);
}