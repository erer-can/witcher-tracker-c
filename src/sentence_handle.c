#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

Bool is_valid_ingredient_sentence(char words[][MAX_WORD_LEN], int word_count)
{
    /**
        * Function Name: is_valid_ingredient_sentence
        *
        * Purpose:
        *    Validates the format of an ingredient sentence.
        *
        * Return:
        *     Bool - Returns TRUE if the format is valid, FALSE otherwise.
        *
        * Side Effects:
        *     - Checks the format of the sentence to ensure it follows the expected structure of 
        *       <ingredient_list> ::= <quantity> <ingredient> | <quantity> <ingredient> "," <ingredient_list>
        *     - The function assumes that the first two words are "Geralt" and "loots".
        *     - The function checks if the quantities are positive integers and if the ingredient names are alphabetic
        *       using the fact that all ingredients have one word names in a cyclic manner.
        *     - The function checks if the quantities have trailing zeros.
        *     - The function also checks if the last word is not a comma.
        *     - The function does not modify any global variables or data structures.
        */
    int curr_index = 2;

    while (curr_index < word_count)
    {
        //we know that following three indices should follow the form of [quantity, ingredient, "",""]
        //so by increasing curr_index by 2 we can check if the next word is a comma, 
        // and by increasing 1 again we will go to the next 3-word block
        if (!is_digit_custom(words[curr_index]))
            return FALSE;
        if (!is_alphabetic_custom(words[curr_index + 1]))
            return FALSE;
        int quantity = atoi(words[curr_index]);
        char ingredient_name[MAX_WORD_LEN];
        strcpy(ingredient_name, words[curr_index + 1]);
        if (quantity <= 0)
            return FALSE;

        curr_index += 2;

        if (curr_index >= word_count)
            break;

        if (strcmp(words[curr_index], ",") != 0)
            return FALSE;

        curr_index++;
    }

    if (strcmp(words[word_count - 1], ",") == 0)
        return FALSE;

    return TRUE;
}

void add_ingredient(Ingredient *ingredients, char *name, int quantity)
{
    /**
        * Function Name: add_ingredient
        *
        * Purpose:
        *    Adds an ingredient to the ingredients array or updates its quantity if it already exists.
        *
        * Parameters:
        *     Ingredient *ingredients - The array of ingredients.
        *     char *name - The name of the ingredient to be added or updated.
        *     int quantity - The quantity of the ingredient to be added or updated.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Modifies the ingredients array by adding a new ingredient or updating the quantity of an existing one.
        *     - The function does allocate the ingredients array if it is full.
        *     - The function does not print any output.
        */
    for (int i = 0; i <= last_added_ingredient_index; i++)
    {
        if (strcmp(ingredients[i].name, name) == 0)
        {
            // If the ingredient already exists, update its quantity and return
            ingredients[i].quantity += quantity;
            return;
        }
    }
    // If the ingredient does not exist, add it to the array
    // Ensure there is enough capacity in the ingredients array
    ensure_ingredient_capacity();
    last_added_ingredient_index++;
    strcpy(ingredients[last_added_ingredient_index].name, name);
    ingredients[last_added_ingredient_index].quantity = quantity;
}

Bool is_valid_trade_sentence(char words[][MAX_WORD_LEN], int word_count)
{
    /**
        * Function Name: is_valid_trade_sentence
        *
        * Purpose:
        *    Validates the format of a trade sentence.
        *
        * Return:
        *     Bool - Returns TRUE if the format is valid, FALSE otherwise.
        *
        * Side Effects:
        *     - Checks the format of the sentence to ensure it follows the expected structure of 
        *       <trophy_list> "for" <ingredient_list>
        *     - The function assumes that the first two words are "Geralt" and "trades".
        *     - The function checks if the quantities are positive integers and if the trophy names are alphabetic
        *       using the fact that all trophies have one word names in a cyclic manner.
        *     - The function checks if the quantities have trailing zeros.
        *     - The function also checks if the last word is not a comma.
        *     - The function does not modify any global variables or data structures.
        */
    int curr_index = 2;
    int trophy_count = 0;
    while (curr_index < word_count && strcmp(words[curr_index], "for") != 0)
    {
        if (!is_digit_custom(words[curr_index]))
            return FALSE;
        if (!is_alphabetic_custom(words[curr_index + 1]))
            return FALSE;
        int quantity = atoi(words[curr_index]);
        if (quantity <= 0 || curr_index + 2 >= word_count)
            return FALSE;

        if (strcmp(words[curr_index + 2], "trophy") != 0)
            return FALSE;

        curr_index += 3;
        trophy_count++;

        if (curr_index < word_count && strcmp(words[curr_index], "for") == 0)
            break;

        if (curr_index >= word_count || strcmp(words[curr_index], ",") != 0)
            return FALSE;

        curr_index++;
    }

    if (curr_index >= word_count || strcmp(words[curr_index], "for") != 0)
        return FALSE;

    if (trophy_count == 1 && strcmp(words[curr_index - 1], ",") == 0)
        return FALSE;

    curr_index++;

    while (curr_index < word_count)
    {
        if (curr_index + 1 >= word_count)
            return FALSE;
        if (!is_digit_custom(words[curr_index]))
            return FALSE;
        if (!is_alphabetic_custom(words[curr_index + 1]))
            return FALSE;

        int quantity = atoi(words[curr_index]);
        if (quantity <= 0)
            return FALSE;

        curr_index += 2;

        if (curr_index >= word_count)
            break;

        if (strcmp(words[curr_index], ",") != 0)
            return FALSE;

        curr_index++;
    }

    return TRUE;
}

Bool check_valid_trade(Trophy *trophies, Trophy *trophies_to_trade, int trade_index)
{
    /**
        * Function Name: check_valid_trade
        *
        * Purpose:
        *    Checks if the trade is valid by comparing the quantities of trophies to be traded with the available trophies.
        *
        * Parameters:
        *     Trophy *trophies - The array of available trophies.
        *     Trophy *trophies_to_trade - The array of trophies to be traded.
        *     int trade_index - The number of trophies to be traded.
        *
        * Return:
        *     Bool - Returns TRUE if the trade is valid, FALSE otherwise.
        *
        * Side Effects:
        *     - Checks if the quantities of trophies to be traded are less than or equal to the available trophies.
        *     - The function does not modify any global variables or data structures.
        */
    for (int i = 0; i < trade_index; i++)
    {
        int found = FALSE;
        for (int j = 0; j <= last_added_trophy_index; j++)
        {
            if (strcmp(trophies_to_trade[i].name, trophies[j].name) == 0)
            {
                // We can break the loop here since we found the matching trophy
                // and we can check the quantity
                // If the quantity to trade is less than or equal to the available quantity
                // we can proceed with the trade
                // If not, the trade is invalid
                if (trophies_to_trade[i].quantity <= trophies[j].quantity)
                {
                    found = TRUE;
                    break;
                }
                else
                {
                    return FALSE;
                }
            }
        }
        // If we didn't find the trophy in the available trophies, the trade is invalid
        // so we return FALSE
        if (!found)
        {
            return FALSE;
        }
    }
    return TRUE;
}

void trade(Ingredient *ingredients, Trophy *trophies, Trophy *trophies_to_trade, int num_trophies_to_trade, char words[][MAX_WORD_LEN], int curr_index, int word_count)
{
    /**
        * Function Name: trade
        *
        * Purpose:
        *    Performs the trade operation by updating the quantities of ingredients and trophies.
        *
        * Parameters:
        *     Ingredient *ingredients - The array of ingredients.
        *     Trophy *trophies - The array of trophies.
        *     Trophy *trophies_to_trade - The array of trophies to be traded.
        *     int num_trophies_to_trade - The number of trophies to be traded.
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int curr_index - The current index in the words array.
        *     int word_count - The total number of words in the input line.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Modifies the ingredients and trophies arrays by updating their quantities based on the trade operation.
        */
    while (curr_index < word_count)
    {
        if (curr_index + 1 >= word_count)
            return;

        int quantity = atoi(words[curr_index]);
        char ingredient_name[MAX_WORD_LEN];
        strcpy(ingredient_name, words[curr_index + 1]);

        int found = 0;
        for (int i = 0; i <= last_added_ingredient_index; i++)
        {
            if (strcmp(ingredients[i].name, ingredient_name) == 0)
            {
                // If the ingredient already exists, update its quantity and return
                ingredients[i].quantity += quantity;
                found = 1;
                break;
            }
        }
        // If the ingredient does not exist, add it to the array
        // Ensure there is enough capacity in the ingredients array
        if (!found)
        {
            ensure_ingredient_capacity();
            last_added_ingredient_index++;
            strcpy(ingredients[last_added_ingredient_index].name, ingredient_name);
            ingredients[last_added_ingredient_index].quantity = quantity;
        }

        curr_index += 2;

        if (curr_index >= word_count)
            break;

        if (strcmp(words[curr_index], ",") == 0)
            curr_index++;
    }

    for (int i = 0; i < num_trophies_to_trade; i++)
    {
        for (int j = 0; j <= last_added_trophy_index; j++)
        {
            //Decrease the quantity of the trophy in the trophies array
            //we don't check if the trophy exists in the trophies array
            //because we already checked it in the check_valid_trade function
            if (strcmp(trophies[j].name, trophies_to_trade[i].name) == 0)
            {
                trophies[j].quantity -= trophies_to_trade[i].quantity;
            }
        }
    }
}

Bool is_valid_brew_sentence(char words[][MAX_WORD_LEN], int word_count, const char *line)
{
    /**
        * Function Name: is_valid_brew_sentence
        *
        * Purpose:
        *    Validates the format of a brew sentence.
        *
        * Return:
        *     Bool - Returns TRUE if the format is valid, FALSE otherwise.
        *
        * Side Effects:
        *     - The function assumes that the first two words are "Geralt" and "brews".
        *     - The function checks if the potion name is valid
        *     - The function checks if the potion name is alphabetic and if the ingredient names are alphabetic
        *       using the fact that all ingredients have one word names in a cyclic manner.
        *     - The function checks if the potion name has trailing spaces.
        *     - The function does not modify any global variables or data structures.
        */
    if (word_count < 3)
        return FALSE;

    for (int i = 2; i < word_count; i++)
    {
        if (!is_alphabetic_custom(words[i]))
            return FALSE;
    }
    char potion_name[MAX_LINE_LENGTH] = "";
    for (int i = 2; i < word_count; i++)
    {
        strcat(potion_name, words[i]);
        if (i < word_count - 1)
            strcat(potion_name, " ");
    }

    if (!is_valid_potion_name_spacing(line, potion_name))
        return FALSE;
    return TRUE;
}

PotionFormula *get_formula(const char *potion_name, PotionFormula *formulas)
{
    /**
        * Function Name: get_formula
        *
        * Purpose:
        *    Retrieves the potion formula for a given potion name.
        *
        * Parameters:
        *     const char *potion_name - The name of the potion to retrieve the formula for.
        *     PotionFormula *formulas - The array of potion formulas.
        *
        * Return:
        *     PotionFormula* - A pointer to the potion formula if found, NULL otherwise.
        *
        * Side Effects:
        *     - Searches for the potion formula in the formulas array based on the potion name.
        *     - The function does not modify any global variables or data structures.
        */
    for (int i = 0; i <= last_added_formula_index; i++)
    {
        if (strcmp(formulas[i].name, potion_name) == 0)
        {
            return &formulas[i];
        }
    }
    return NULL;
}

Bool has_formula(const char *potion_name, PotionFormula *formulas)
{
    /**
        * Function Name: has_formula
        *
        * Purpose:
        *    Checks if a potion formula exists for a given potion name.
        *
        * Parameters:
        *     const char *potion_name - The name of the potion to check for a formula.
        *     PotionFormula *formulas - The array of potion formulas.
        *
        * Return:
        *     Bool - Returns TRUE if the formula exists, FALSE otherwise.
        *
        * Side Effects:
        *     - Searches for the potion formula in the formulas array based on the potion name.
        *     - The function does not modify any global variables or data structures.
        */
    return get_formula(potion_name, formulas) != NULL;
}

Bool can_brew(const char *potion_name, Ingredient *inventory, PotionFormula *formulas)
{
    /**
        * Function Name: can_brew
        *
        * Purpose:
        *    Checks if a potion can be brewed based on the available ingredients in the inventory.
        *
        * Parameters:
        *     const char *potion_name - The name of the potion to check if it can be brewed.
        *     Ingredient *inventory - The array of available ingredients in the inventory.
        *     PotionFormula *formulas - The array of potion formulas.
        *
        * Return:
        *     Bool - Returns TRUE if the potion can be brewed, FALSE otherwise.
        *
        * Side Effects:
        *     - Checks if all required ingredients for the potion formula are available in sufficient quantities in the inventory.
        *     - The function does not modify any global variables or data structures.
        */
    // Check if the potion formula exists
    PotionFormula *formula = get_formula(potion_name, formulas);
    if (formula == NULL)
        return FALSE;

    for (int i = 0; i < formula->ingredient_count; i++)
    {
        int found = FALSE;
        for (int j = 0; j <= last_added_ingredient_index; j++)
        {
            // Check if the ingredient exists in the inventory and has sufficient quantity
            // If the ingredient is found in the inventory and its quantity is sufficient
            // we can break the loop and check the next ingredient
            // If the ingredient is not found in the inventory or its quantity is insufficient
            // we can return FALSE
            if (strcmp(inventory[j].name, formula->ingredients[i].name) == 0 &&
                inventory[j].quantity >= formula->ingredients[i].quantity)
            {
                found = TRUE;
                break;
            }
        }
        if (!found)
            return FALSE;
    }
    // If all required ingredients are found in sufficient quantities, return TRUE
    return TRUE;
}

void brew_potion(const char *potion_name, Ingredient *inventory, Potion *potions, PotionFormula *formulas)
{
    /**
        * Function Name: brew_potion
        *
        * Purpose:
        *    Brews a potion by checking if the required ingredients are available and updating the inventory and potions array.
        *
        * Parameters:
        *     const char *potion_name - The name of the potion to be brewed.
        *     Ingredient *inventory - The array of available ingredients in the inventory.
        *     Potion *potions - The array of brewed potions.
        *     PotionFormula *formulas - The array of potion formulas.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Modifies the inventory and potions arrays by updating their quantities based on the brewed potion.
        */
    // Check if the potion can be brewed
    PotionFormula *formula = get_formula(potion_name, formulas);
    if (formula == NULL)
        return;

    for (int i = 0; i < formula->ingredient_count; i++)
    {
        //we don't check if the ingredient exists in the inventory
        //because we already checked it in the can_brew function
        //and we know that the quantity is sufficient
        //so we just decrease the quantity of the ingredient in the inventory
        for (int j = 0; j <= last_added_ingredient_index; j++)
        {
            if (strcmp(inventory[j].name, formula->ingredients[i].name) == 0)
            {
                inventory[j].quantity -= formula->ingredients[i].quantity;
            }
        }
    }

    add_potion(potions, potion_name);
    printf("Alchemy item created: %s\n", potion_name);
}

void add_potion(Potion *potions, const char *name)
{
    /**
        * Function Name: add_potion
        *
        * Purpose:
        *    Adds a potion to the potions array or updates its quantity if it already exists.
        *
        * Parameters:
        *     Potion *potions - The array of potions.
        *     const char *name - The name of the potion to be added or updated.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Modifies the potions array by adding a new potion or updating the quantity of an existing one.
        *     - The function does allocate the potions array if it is full.
        */
    // Check if the potion already exists in the potions array
    // If it does, increase its quantity and return
    for (int i = 0; i <= last_added_potion_index; i++)
    {
        if (strcmp(potions[i].name, name) == 0)
        {
            potions[i].quantity++;
            return;
        }
    }
    // If the potion does not exist, add it to the array
    // Ensure there is enough capacity in the potions array
    ensure_potion_capacity();
    last_added_potion_index++;
    strcpy(potions[last_added_potion_index].name, name);
    potions[last_added_potion_index].quantity = 1;
}

Bool is_valid_learn_sentence(char words[][MAX_WORD_LEN], int word_count, const char *line)
{
    /**
        * Function Name: is_valid_learn_sentence
        *
        * Purpose:
        *    Validates the format of a learn sentence.
        *
        * Return:
        *     Bool - Returns TRUE if the format is valid, FALSE otherwise.
        *
        * Side Effects:
        *     - The function assumes that the first two words are "Geralt" and "learns".
        *     - The function checks if the potion name is valid
        *     - The function checks if the potion name is alphabetic and if the ingredient names are alphabetic
        *       using the fact that all ingredients have one word names in a cyclic manner.
        *     - The function checks if the potion name has trailing spaces.
        *     - The function does not modify any global variables or data structures.
        */
    if (word_count < 5)
        return FALSE;

    if (word_count == 8 && strcmp(words[3], "sign") == 0)
    {
        //this structure gives a learn a sign against a monster
        if (!is_alphabetic_custom(words[2]))
            return FALSE;
        if (strcmp(words[4], "is") != 0 ||
            strcmp(words[5], "effective") != 0 ||
            strcmp(words[6], "against") != 0)
            return FALSE;
        if (!is_alphabetic_custom(words[7]))
            return FALSE;
        return TRUE;
    }

    int potion_idx = -1;
    for (int i = 2; i < word_count; i++)
    {
        if (strcmp(words[i], "potion") == 0)
        {
            potion_idx = i;
            break;
        }
    }
    if (potion_idx == -1)
        return FALSE;

    if (potion_idx == 2)
        return FALSE;

    for (int i = 2; i < potion_idx; i++)
    {
        if (!is_alphabetic_custom(words[i]))
            return FALSE;
    }

    char potion_name[MAX_LINE_LENGTH] = "";
    for (int i = 2; i < potion_idx; i++)
    {
        strcat(potion_name, words[i]);
        if (i < potion_idx - 1)
            strcat(potion_name, " ");
    }
    // Check if the potion name is valid
    if (!is_valid_potion_name_spacing(line, potion_name))
        return FALSE;

    if (potion_idx + 1 >= word_count)
        return FALSE;

    if (strcmp(words[potion_idx + 1], "is") == 0)
    {
        //this structure gives a learn a potion against a monster
        if (word_count != potion_idx + 5)
            return FALSE;
        if (strcmp(words[potion_idx + 2], "effective") != 0 ||
            strcmp(words[potion_idx + 3], "against") != 0)
            return FALSE;
        if (!is_alphabetic_custom(words[potion_idx + 4]))
            return FALSE;
        return TRUE;
    }
    else if (strcmp(words[potion_idx + 1], "consists") == 0)
    {
        //this structure gives a learn a potion formula
        if (potion_idx + 2 >= word_count)
            return FALSE;
        if (strcmp(words[potion_idx + 2], "of") != 0)
            return FALSE;

        int curr_index = potion_idx + 3;
        if (curr_index >= word_count)
            return FALSE;

        while (curr_index < word_count)
        {
            if (curr_index + 1 >= word_count)
                return FALSE;
            if (!is_digit_custom(words[curr_index]))
                return FALSE;
            if (!is_alphabetic_custom(words[curr_index + 1]))
                return FALSE;
            int quantity = atoi(words[curr_index]);
            if (quantity <= 0)
                return FALSE;
            if (!is_alphabetic_custom(words[curr_index + 1]))
                return FALSE;
            curr_index += 2;

            if (curr_index >= word_count)
                break;
            if (strcmp(words[curr_index], ",") != 0)
                return FALSE;
            curr_index++;
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

Bool learn_potion_formula(char words[][MAX_WORD_LEN], int word_count, PotionFormula *formulas)
{
    /**
        * Function Name: learn_potion_formula
        *
        * Purpose:
        *    Learns a new potion formula by adding it to the formulas array.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int word_count - The total number of words in the input line.
        *     PotionFormula *formulas - The array of potion formulas.
        *
        * Return:
        *     Bool - Returns TRUE if the formula was learned successfully, FALSE otherwise.
        *
        * Side Effects:
        *     - Modifies the formulas array by adding a new potion formula.
        */
    int i = 2;
    char potion_name[MAX_WORD_LEN] = "";
    while (i < word_count && strcmp(words[i], "potion") != 0)
    {
        strcat(potion_name, words[i]);
        strcat(potion_name, " ");
        i++;
    }
    potion_name[strlen(potion_name) - 1] = '\0';
    i += 3;

    if (has_formula(potion_name, formulas))
    {
        printf("Already known formula\n");
        return TRUE;
    }

    //if the potion formula is not known, add it to the array
    ensure_formula_capacity();
    last_added_formula_index++;

    PotionFormula *formula = &formulas[last_added_formula_index];
    strcpy(formula->name, potion_name);
    formula->ingredient_capacity = 4;
    formula->ingredient_count = 0;
    formula->ingredients = malloc(sizeof(Ingredient) * formula->ingredient_capacity);
    if (!formula->ingredients) return FALSE;

    while (i < word_count)
    {
        if (i + 1 >= word_count) return FALSE;
        if (!is_digit_custom(words[i]) || !is_alphabetic_custom(words[i + 1])) return FALSE;

        int quantity = atoi(words[i]);
        if (quantity <= 0) return FALSE;

        if (formula->ingredient_count >= formula->ingredient_capacity)
        {
            formula->ingredient_capacity *= 2;
            formula->ingredients = realloc(formula->ingredients, sizeof(Ingredient) * formula->ingredient_capacity);
            if (!formula->ingredients) return FALSE;
        }

        strcpy(formula->ingredients[formula->ingredient_count].name, words[i + 1]);
        formula->ingredients[formula->ingredient_count].quantity = quantity;
        formula->ingredient_count++;

        i += 2;
        if (i < word_count && strcmp(words[i], ",") == 0) i++;
    }

    printf("New alchemy formula obtained: %s\n", potion_name);
    return TRUE;
}

Bool learn_effectiveness(char words[][MAX_WORD_LEN], int word_count, Monster *monsters)
{
    /**
        * Function Name: learn_effectiveness
        *
        * Purpose:
        *    Learns the effectiveness of a sign or potion against a monster by adding it to the monster's entry.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int word_count - The total number of words in the input line.
        *     Monster *monsters - The array of monsters.
        *
        * Return:
        *     Bool - Returns TRUE if the effectiveness was learned successfully, FALSE otherwise.
        *
        * Side Effects:
        *     - Modifies the monsters array by adding a new effectiveness entry for the specified monster.
        */
    char monster_name[MAX_WORD_LEN];

    char thing_name[MAX_WORD_LEN] = "";
    char thing_type[MAX_WORD_LEN] = "";

    int i = 2;
    while (i < word_count && strcmp(words[i], "sign") != 0 && strcmp(words[i], "potion") != 0)
    {
        strcat(thing_name, words[i]);
        if (i + 1 < word_count && strcmp(words[i + 1], "sign") != 0 && strcmp(words[i + 1], "potion") != 0)
            strcat(thing_name, " ");
        i++;
    }

    if (i >= word_count)
        return FALSE;

    strcpy(thing_type, words[i]);
    strcpy(monster_name, words[word_count - 1]);

    int monster_index = -1;
    for (int i = 0; i <= last_added_monster_index; i++) {
        if (strcmp(monsters[i].name, monster_name) == 0) {
            monster_index = i;
            break;
        }
    }

    if (monster_index == -1) {
        ensure_monster_capacity();
        last_added_monster_index++;
        monster_index = last_added_monster_index;
        Monster *m = &monsters[monster_index];
        strcpy(m->name, monster_name);

        m->sign_capacity = 4;
        m->sign_count = 0;
        m->signs = malloc(m->sign_capacity * sizeof(Sign));

        m->potion_capacity = 4;
        m->potion_count = 0;
        m->potions = malloc(m->potion_capacity * sizeof(Potion));

        if (strcmp(thing_type, "sign") == 0) {
            ensure_monster_sign_capacity(m);
            strcpy(m->signs[m->sign_count].name, thing_name);
            m->signs[m->sign_count].quantity = 1;
            m->sign_count++;
        } else {
            ensure_monster_potion_capacity(m);
            strcpy(m->potions[m->potion_count].name, thing_name);
            m->potions[m->potion_count].quantity = 1;
            m->potion_count++;
        }

        printf("New bestiary entry added: %s\n", monster_name);
        return TRUE;
    }

    Monster *m = &monsters[monster_index];

    if (strcmp(thing_type, "sign") == 0) {
        for (int i = 0; i < m->sign_count; i++) {
            if (strcmp(m->signs[i].name, thing_name) == 0) {
                printf("Already known effectiveness\n");
                return TRUE;
            }
        }
        ensure_monster_sign_capacity(m);
        strcpy(m->signs[m->sign_count].name, thing_name);
        m->signs[m->sign_count].quantity = 1;
        m->sign_count++;
    } else {
        for (int i = 0; i < m->potion_count; i++) {
            if (strcmp(m->potions[i].name, thing_name) == 0) {
                printf("Already known effectiveness\n");
                return TRUE;
            }
        }
        ensure_monster_potion_capacity(m);
        strcpy(m->potions[m->potion_count].name, thing_name);
        m->potions[m->potion_count].quantity = 1;
        m->potion_count++;
    }

    printf("Bestiary entry updated: %s\n", monster_name);
    return TRUE;
}

Bool is_valid_encounter_sentence(char words[][MAX_WORD_LEN], int word_count)
{
    /**
        * Function Name: is_valid_encounter_sentence
        *
        * Purpose:
        *    Validates the format of an encounter sentence.
        *
        * Return:
        *     Bool - Returns TRUE if the format is valid, FALSE otherwise.
        *
        * Side Effects:
        *     - The function assumes that the first two words are "Geralt" and "encounters".
        *     - The function checks if the monster name is alphabetic and if the word count is exactly 4.
        *     - The function does not modify any global variables or data structures.
        */
    if (word_count != 4)
        return FALSE;

    if (strcmp(words[0], "Geralt") != 0)
        return FALSE;
    if (strcmp(words[1], "encounters") != 0)
        return FALSE;
    if (strcmp(words[2], "a") != 0)
        return FALSE;
    if (!is_alphabetic_custom(words[3]))
        return FALSE;

    return TRUE;
}

void handle_encounter(char words[][MAX_WORD_LEN], int word_count, Monster *monsters, Potion *potions, Trophy *trophies)
{
    /**
        * Function Name: handle_encounter
        *
        * Purpose:
        *    Handles the encounter with a monster by checking if Geralt is prepared and updating the trophies.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int word_count - The total number of words in the input line.
        *     Monster *monsters - The array of monsters.
        *     Potion *potions - The array of potions.
        *     Trophy *trophies - The array of trophies.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Modifies the trophies array by updating the quantity of the trophy obtained from the encounter.
        */
    if (word_count < 4 || strcmp(words[2], "a") != 0)
    {
        printf("INVALID\n");
        return;
    }

    char monster_name[MAX_WORD_LEN];
    strcpy(monster_name, words[3]);

    int monster_index = -1;
    for (int i = 0; i <= last_added_monster_index; i++)
    {
        // Check if the monster name matches the one in the monsters array
        if (strcmp(monsters[i].name, monster_name) == 0)
        {
            monster_index = i;
            break;
        }
    }

    if (monster_index == -1)
    {
        printf("Geralt is unprepared and barely escapes with his life\n");
        return;
    }

    Monster *m = &monsters[monster_index];

    int has_effective_sign = m->sign_count > 0;
    int has_effective_potion = 0;

    //checks if Geralt has an effective potion against the monster
    for (int i = 0; i < m->potion_count; i++)
    {
        for (int j = 0; j <= last_added_potion_index; j++)
        {
            if (strcmp(m->potions[i].name, potions[j].name) == 0 && potions[j].quantity > 0)
            {
                has_effective_potion = 1;
                break;
            }
        }
    }

    if (!has_effective_sign && !has_effective_potion)
    {
        //if no sign or potion is effective against the monster we can't fight
        printf("Geralt is unprepared and barely escapes with his life\n");
        return;
    }

    printf("Geralt defeats %s\n", monster_name);

    //uses all possessed potions just in case
    for (int i = 0; i < m->potion_count; i++)
    {
        for (int j = 0; j <= last_added_potion_index; j++)
        {
            if (strcmp(m->potions[i].name, potions[j].name) == 0 && potions[j].quantity > 0)
            {
                potions[j].quantity--;
            }
        }
    }

    for (int i = 0; i <= last_added_trophy_index; i++)
    {
        // Check if the trophy name matches the one in the trophies array, then increase by 1
        if (strcmp(trophies[i].name, monster_name) == 0)
        {
            trophies[i].quantity++;
            return;
        }
    }
    // If the trophy does not exist, add it to the array
    // Ensure there is enough capacity in the trophies array
    ensure_trophy_capacity();
    last_added_trophy_index++;
    strcpy(trophies[last_added_trophy_index].name, monster_name);
    trophies[last_added_trophy_index].quantity = 1;
}