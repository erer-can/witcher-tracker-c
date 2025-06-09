#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

int last_added_ingredient_index = -1;
int last_added_potion_index = -1;
int last_added_sign_index = -1;
int last_added_monster_index = -1;
int last_added_trophy_index = -1;
int last_added_formula_index = -1;

int ingredient_capacity = 2;
int potion_capacity = 2;
int trophy_capacity = 2;
int monster_capacity = 2;
int formula_capacity = 2;
int sign_capacity = 2;

Ingredient *ingredients;
Potion *potions;
Sign *signs;
Monster *monsters;
Trophy *trophies;
PotionFormula *formulas;

void execute_line(char *line)
{
    /**
    * Function Name: execute_line
    *
    * Purpose:
    *    Executes a line of input by parsing it, deciding its type and validity, 
    *    perform the necessary action if valid, and print the result,
    *    exits if type is EXIT.
    *
    * Parameters:
    *     char *line - The line of input to be executed.
    *
    * Return:
    *     void - This function does not return a value.
    *
    * Side Effects:
    *     - Modifies the necessary global variables ingredients, potions, trophies, formulas, monsters, and signs, its indices and capacities.
    *     - Allocates and reallocates memory for ingredients, potions, trophies, formulas, monsters, and signs.
    *     - Prints the result of the executed line.
    *     - Exits if the type is EXIT.
    *     - No changes if the line is invalid.
    */
    remove_trailing_newline(line);
    remove_trailing_spaces(line);

    char words[550][MAX_WORD_LEN];
    int word_count = split_into_words(line, words);
    LineType type = detect_type(words, word_count);

    if (type == SENTENCE)
    {
        if (strcmp(words[0], "Geralt") != 0)
        {
            printf("INVALID\n");
            return;
        }
        if (strcmp(words[2], ",") == 0)
        {
            printf("INVALID\n");
            return;
        }
        Sentence sentence_type = detect_sentence(words);
        if (sentence_type == -1)
        {
            printf("INVALID\n");
            return;
        }

        if (sentence_type == LOOT)
        {
            if (is_valid_ingredient_sentence(words, word_count))
            {
                int curr_index = 2;
                while (curr_index < word_count)
                {
                    if (strcmp(words[curr_index], ",") == 0)
                    {
                        curr_index++;
                        continue;
                    }
                    int quantity = atoi(words[curr_index]);
                    if (curr_index + 1 >= word_count)
                        break;
                    char ingredient[MAX_WORD_LEN];
                    strcpy(ingredient, words[curr_index + 1]);

                    if (last_added_ingredient_index + 1 >= ingredient_capacity)
                    {
                        ingredient_capacity *= 2;
                        ingredients = realloc(ingredients, ingredient_capacity * sizeof(Ingredient));
                    }
                    add_ingredient(ingredients, ingredient, quantity);

                    curr_index += 2;
                }
                printf("Alchemy ingredients obtained\n");
            }
            else
            {
                printf("INVALID\n");
                return;
            }
        }
        else if (sentence_type == TRADE)
        {
            if (is_valid_trade_sentence(words, word_count))
            {
                Trophy *trophies_to_trade = malloc(sizeof(Trophy) * trophy_capacity);

                int curr_index = 2;
                int trade_index = 0;
                while (curr_index < word_count && strcmp(words[curr_index], "for") != 0)
                {
                    int quantity = atoi(words[curr_index]);
                    if (quantity <= 0 || curr_index + 2 >= word_count)
                        return;

                    if (strcmp(words[curr_index + 2], "trophy") != 0)
                        return;

                    strcpy(trophies_to_trade[trade_index].name, words[curr_index + 1]);
                    trophies_to_trade[trade_index].quantity = quantity;
                    trade_index++;

                    curr_index += 3;

                    if (curr_index < word_count && strcmp(words[curr_index], "for") == 0)
                        break;

                    if (curr_index >= word_count || strcmp(words[curr_index], ",") != 0)
                        return;

                    curr_index++;
                }
                if (curr_index >= word_count || strcmp(words[curr_index], "for") != 0)
                    return;
                curr_index++;
                if (check_valid_trade(trophies, trophies_to_trade, trade_index))
                {
                    trade(ingredients, trophies, trophies_to_trade, trade_index, words, curr_index, word_count);
                    printf("Trade successful\n");
                }
                else
                {
                    printf("Not enough trophies\n");
                    return;
                }
                free(trophies_to_trade);
            }
            else
            {
                printf("INVALID\n");
                return;
            }
        }

        if (sentence_type == BREW)
        {
            if (word_count < 3)
            {
                printf("INVALID\n");
                return;
            }

            if (!is_valid_brew_sentence(words, word_count, line))
            {
                printf("INVALID\n");
                return;
            }

            char potion_name[MAX_WORD_LEN] = "";
            for (int i = 2; i < word_count; i++)
            {
                strcat(potion_name, words[i]);
                if (i < word_count - 1)
                    strcat(potion_name, " ");
            }

            if (!has_formula(potion_name, formulas))
            {
                printf("No formula for %s\n", potion_name);
                return;
            }

            if (!can_brew(potion_name, ingredients, formulas))
            {
                printf("Not enough ingredients\n");
                return;
            }

            if (last_added_potion_index + 1 >= potion_capacity)
            {
                potion_capacity *= 2;
                potions = realloc(potions, potion_capacity * sizeof(Potion));
            }

            brew_potion(potion_name, ingredients, potions, formulas);
        }
        else if (sentence_type == LEARN)
        {
            if (!is_valid_learn_sentence(words, word_count, line))
            {
                printf("INVALID\n");
                return;
            }
            for (int i = 0; i < word_count - 3; i++)
            {
                if (strcmp(words[i], "potion") == 0 &&
                    strcmp(words[i + 1], "consists") == 0 &&
                    strcmp(words[i + 2], "of") == 0)
                {
                    if (!learn_potion_formula(words, word_count, formulas))
                    {
                        printf("INVALID\n");
                    }
                    return;
                }
            }

            for (int i = 2; i < word_count - 4; i++)
            {
                if ((strcmp(words[i], "sign") == 0 || strcmp(words[i], "potion") == 0) &&
                    strcmp(words[i + 1], "is") == 0 &&
                    strcmp(words[i + 2], "effective") == 0 &&
                    strcmp(words[i + 3], "against") == 0)
                {
                    if (!learn_effectiveness(words, word_count, monsters))
                    {
                        printf("INVALID\n");
                    }
                    return;
                }
            }

            printf("INVALID\n");
            return;
        }
        else if (sentence_type == ENCOUNTER)
        {
            if (!is_valid_encounter_sentence(words, word_count))
            {
                printf("INVALID\n");
                return;
            }

            if (last_added_trophy_index + 1 >= trophy_capacity)
            {
                trophy_capacity *= 2;
                trophies = realloc(trophies, trophy_capacity * sizeof(Trophy));
            }

            handle_encounter(words, word_count, monsters, potions, trophies);
        }
    }
    else if (type == QUESTION)
    {
        Question question_type = detect_question(words, word_count);
        if (question_type == INGREDIENT)
        {
            handle_specific_ingredient_query(words, word_count);
        }
        else if (question_type == POTION)
        {
            handle_specific_potion_query(words, word_count, line);
        }
        else if (question_type == TROPHY)
        {
            handle_specific_trophy_query(words, word_count);
        }
        else if (question_type == ALL_INGREDIENTS)
        {
            handle_all_ingredients_query();
        }
        else if (question_type == ALL_POTIONS)
        {
            handle_all_potions_query();
        }
        else if (question_type == ALL_TROPHIES)
        {
            handle_all_trophies_query();
        }
        else if (question_type == POTION_FORMULA)
        {
            handle_potion_recipe_query(words, word_count, line);
        }
        else if (question_type == MONSTER)
        {
            handle_monster_query(words, word_count);
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (type == EXIT)
    {
        exit(0);
    }
}

int main()
{
    ingredients = malloc(sizeof(Ingredient) * ingredient_capacity);
    potions = malloc(sizeof(Potion) * potion_capacity);
    trophies = malloc(sizeof(Trophy) * trophy_capacity);
    formulas = malloc(sizeof(PotionFormula) * formula_capacity);
    monsters = malloc(sizeof(Monster) * monster_capacity);
    signs = malloc(sizeof(Sign) * sign_capacity);

    char line[1025];
    while (1)
    {
        printf(">> ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin))
            break;

        execute_line(line);
    }

    // FILE *file = fopen("../test-cases/input1.txt", "r");
    // while(fgets(line, sizeof(line), file))
    // {
    //     execute_line(line);
    // }
    // fclose(file);

    free(ingredients);
    free(potions);
    free(trophies);
    free(formulas);
    free(monsters);
    free(signs);

    return 0;
}
