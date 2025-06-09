#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

void ensure_ingredient_capacity() {
    /**
     * Function Name: ensure_ingredient_capacity
     *
     * Purpose:
     *    Ensures that the ingredients array has enough capacity to add a new ingredient.
     *
     * Parameters:
     *     void - This function does not take any parameters.
     *
     * Return:
     *     void - This function does not return a value.
     *
     * Side Effects:
     *     - Doubles the capacity of the ingredients array if the current capacity is not enough.
     *     - Reallocates memory for the ingredients array to accommodate the new capacity.
     *     - Updates the global variable ingredient_capacity to reflect the new capacity.
     */
    if (last_added_ingredient_index + 1 >= ingredient_capacity) {
        ingredient_capacity *= 2;
        ingredients = realloc(ingredients, ingredient_capacity * sizeof(Ingredient));
    }
}

void ensure_potion_capacity() {
    /**
     * Function Name: ensure_potion_capacity
     *
     * Purpose:
     *    Ensures that the potions array has enough capacity to add a new potion.
     *
     * Parameters:
     *     void - This function does not take any parameters.
     *
     * Return:
     *     void - This function does not return a value.
     *
     * Side Effects:
     *     - Doubles the capacity of the potions array if the current capacity is not enough.
     *     - Reallocates memory for the potions array to accommodate the new capacity.
     *     - Updates the global variable potion_capacity to reflect the new capacity.
     */
    if (last_added_potion_index + 1 >= potion_capacity) {
        potion_capacity *= 2;
        potions = realloc(potions, potion_capacity * sizeof(Potion));
    }
}

void ensure_trophy_capacity() {
    /**
     * Function Name: ensure_trophy_capacity
     *
     * Purpose:
     *    Ensures that the trophies array has enough capacity to add a new trophy.
     *
     * Parameters:
     *     void - This function does not take any parameters.
     *
     * Return:
     *     void - This function does not return a value.
     *
     * Side Effects:
     *     - Doubles the capacity of the trophies array if the current capacity is not enough.
     *     - Reallocates memory for the trophies array to accommodate the new capacity.
     *     - Updates the global variable trophy_capacity to reflect the new capacity.
     */
    if (last_added_trophy_index + 1 >= trophy_capacity) {
        trophy_capacity *= 2;
        trophies = realloc(trophies, trophy_capacity * sizeof(Trophy));
    }
}

void ensure_monster_capacity() {
    /**
     * Function Name: ensure_monster_capacity
     *
     * Purpose:
     *    Ensures that the monsters array has enough capacity to add a new monster.
     *
     * Parameters:
     *     void - This function does not take any parameters.
     *
     * Return:
     *     void - This function does not return a value.
     *
     * Side Effects:
     *     - Doubles the capacity of the monsters array if the current capacity is not enough.
     *     - Reallocates memory for the monsters array to accommodate the new capacity.
     *     - Updates the global variable monster_capacity to reflect the new capacity.
     */
    if (last_added_monster_index + 1 >= monster_capacity) {
        monster_capacity *= 2;
        monsters = realloc(monsters, monster_capacity * sizeof(Monster));
    }
}

void ensure_formula_capacity() {
    /**
     * Function Name: ensure_formula_capacity
     *
     * Purpose:
     *    Ensures that the formulas array has enough capacity to add a new formula.
     *
     * Parameters:
     *     void - This function does not take any parameters.
     *
     * Return:
     *     void - This function does not return a value.
     *
     * Side Effects:
     *     - Doubles the capacity of the formulas array if the current capacity is not enough.
     *     - Reallocates memory for the formulas array to accommodate the new capacity.
     *     - Updates the global variable formula_capacity to reflect the new capacity.
     */
    if (last_added_formula_index + 1 >= formula_capacity) {
        formula_capacity *= 2;
        formulas = realloc(formulas, formula_capacity * sizeof(PotionFormula));
    }
}

void ensure_sign_capacity() {
    /**
     * Function Name: ensure_sign_capacity
     *
     * Purpose:
     *    Ensures that the signs array has enough capacity to add a new sign.
     *
     * Parameters:
     *     void - This function does not take any parameters.
     *
     * Return:
     *     void - This function does not return a value.
     *
     * Side Effects:
     *     - Doubles the capacity of the signs array if the current capacity is not enough.
     *     - Reallocates memory for the signs array to accommodate the new capacity.
     *     - Updates the global variable sign_capacity to reflect the new capacity.
     */
    if (last_added_sign_index + 1 >= sign_capacity) {
        sign_capacity *= 2;
        signs = realloc(signs, sign_capacity * sizeof(Sign));
    }
}

void ensure_monster_sign_capacity(Monster *m) {
    /**
     * Function Name: ensure_monster_sign_capacity
     *
     * Purpose:
     *    Ensures that the signs array of a monster has enough capacity to add a new sign.
     *
     * Parameters:
     *     Monster *m - The monster whose signs array needs to be checked.
     *
     * Return:
     *     void - This function does not return a value.
     *
     * Side Effects:
     *     - Doubles the capacity of the monster's signs array if the current capacity is not enough.
     *     - Reallocates memory for the monster's signs array to accommodate the new capacity.
     *     - Updates the global variable sign_capacity to reflect the new capacity.
     */
    if (m->sign_count >= m->sign_capacity) {
        m->sign_capacity *= 2;
        m->signs = realloc(m->signs, m->sign_capacity * sizeof(Sign));
    }
}

void ensure_monster_potion_capacity(Monster *m) {
    /**
     * Function Name: ensure_monster_potion_capacity
     *
     * Purpose:
     *    Ensures that the potions array of a monster has enough capacity to add a new potion.
     *
     * Parameters:
     *     Monster *m - The monster whose potions array needs to be checked.
     *
     * Return:
     *     void - This function does not return a value.
     *
     * Side Effects:
     *     - Doubles the capacity of the monster's potions array if the current capacity is not enough.
     *     - Reallocates memory for the monster's potions array to accommodate the new capacity.
     *     - Updates the global variable potion_capacity to reflect the new capacity.
    */
    if (m->potion_count >= m->potion_capacity) {
        m->potion_capacity *= 2;
        m->potions = realloc(m->potions, m->potion_capacity * sizeof(Potion));
    }
}