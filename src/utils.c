#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

void remove_trailing_newline(char *line)
{
    /**
        * Function Name: remove_trailing_newline
        *
        * Purpose:
        *    Removes the trailing newline character from a string.
        * 
        * Parameters:
        *     char *line - The string from which to remove the trailing newline.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Modifies the input string by replacing the trailing newline character with a null terminator.
        *     - The function does not allocate or reallocate memory.
        *     - The function does not print any output.
        *     - The function does not modify any global variables or data structures.
     */
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
    }
}

void remove_trailing_spaces(char *line)
{
    /**
        * Function Name: remove_trailing_spaces
        *
        * Purpose:
        *    Removes trailing spaces and tabs from a string.
        *
        * Parameters:
        *     char *line - The string from which to remove trailing spaces and tabs.
        *
        * Return:
        *     void - This function does not return a value.
        *
        * Side Effects:
        *     - Modifies the input string by replacing trailing spaces and tabs with null terminators.
        *     - The function does not allocate or reallocate memory.
        *     - The function does not print any output.
        *     - The function does not modify any global variables or data structures.
     */
    size_t len = strlen(line);
    while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'))
    {
        line[--len] = '\0';
    }
}

int split_into_words(char *line, char words[][MAX_WORD_LEN])
{
    /**
        * Function Name: split_into_words
        *
        * Purpose:
        *    Splits a string into words based on spaces, commas, and question marks.
        *
        * Parameters:
        *     char *line - The string to be split into words.
        *     char words[][MAX_WORD_LEN] - The array to store the split words.
        *
        * Return:
        *     int - The number of words in the input string.
        *
        * Side Effects:
        *     - Modifies the input array by storing the split words.
        *     - The function treats spaces as delimiters and ignores leading spaces.
        *     - The function treats consecutive spaces as a single delimiter.
        *     - Treats commas and question marks as separate words even if they are smushed to a word.
        *     - The function does not allocate or reallocate memory.
        *     - The function does not print any output.
        *     - The function does not modify any global variables or data structures.
     */
    int count = 0;
    int i = 0;
    while (line[i] != '\0')
    {
        while (line[i] == ' ')
            i++;

        if (line[i] == '\0')
            break;

        if (line[i] == ',' || line[i] == '?')
        {
            words[count][0] = line[i];
            words[count][1] = '\0';
            count++;
            i++;
        }
        else
        {
            int j = 0;
            while (line[i] != '\0' && line[i] != ' ' && line[i] != ',' && line[i] != '?')
            {
                if (j < MAX_WORD_LEN - 1)
                {
                    words[count][j++] = line[i];
                }
                i++;
            }
            words[count][j] = '\0';
            count++;
        }
    }

    return count;
}

Bool is_alphabetic_custom(const char *token)
{
    /**
     * Function Name: is_alphabetic_custom
     *
     * Purpose:
     *    Checks if a given string consists only of alphabetic characters.
     *
     * Parameters:
     *     const char *token - The string to be checked for alphabetic characters.
     *
     * Return:
     *     Bool - TRUE if the string is alphabetic, FALSE otherwise.
     *
     * Side Effects:
     *     - The function does not modify the input string.
     *     - The function does not allocate or reallocate memory.
     *     - The function does not print any output.
     *     - The function does not modify any global variables or data structures.
     */
    for (int i = 0; token[i] != '\0'; i++)
    {
        char c = token[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
        {
            return FALSE;
        }
    }
    return TRUE;
}

Bool is_digit_custom(const char *token)
{
    /**
     * Function Name: is_digit_custom
     *
     * Purpose:
     *    Checks if a given string consists only of digits and does not have a leading zero.
     *
     * Parameters:
     *     const char *token - The string to be checked for digits.
     *
     * Return:
     *     Bool - TRUE if the string is numeric, FALSE otherwise.
     *
     * Side Effects:
     *     - The function does not modify the input string.
     *     - The function does not allocate or reallocate memory.
     *     - The function does not print any output.
     *     - The function does not modify any global variables or data structures.
     */
    if(token[0] == '0')
    {
        return FALSE;
    }
    for (int i = 0; token[i] != '\0'; i++)
    {
        char c = token[i];
        if (!(c >= '0' && c <= '9'))
        {
            return FALSE;
        }
    }
    return TRUE;
}

int cmpIngredient(const void *a, const void *b)
{
    /**
     * Function Name: cmpIngredient
     *
     * Purpose:
     *    Compares two ingredients based on their names for sorting.
     *
     * Parameters:
     *     const void *a - Pointer to the first ingredient.
     *     const void *b - Pointer to the second ingredient.
     *
     * Return:
     *     int - Negative if a < b, positive if a > b, zero if equal.
     *
     * Side Effects:
     *     - Compares ingredients based on their names using strcmp, 
     *       returns a negative value if the first ingredient's name comes before the second ingredient's name, 
     *       a positive value if it comes after, and zero if they are equal.
     *     - The function does not modify the input ingredients.
     *     - The function does not allocate or reallocate memory.
     *     - The function does not print any output.
     *     - The function does not modify any global variables or data structures.
    */
    return strcmp(((Ingredient *)a)->name, ((Ingredient *)b)->name);
}
int cmpPotion(const void *a, const void *b)
{
    /**
     * Function Name: cmpPotion
     *
     * Purpose:
     *    Compares two potions based on their names for sorting.
     *
     * Parameters:
     *     const void *a - Pointer to the first potion.
     *     const void *b - Pointer to the second potion.
     *
     * Return:
     *     int - Negative if a < b, positive if a > b, zero if equal.
     *
     * Side Effects:
     *     - Compares potions based on their names using strcmp, 
     *       returns a negative value if the first potion's name comes before the second potion's name, 
     *       a positive value if it comes after, and zero if they are equal.
     *     - The function does not modify the input potions.
     *     - The function does not allocate or reallocate memory.
     *     - The function does not print any output.
     *     - The function does not modify any global variables or data structures.
    */
    return strcmp(((Potion *)a)->name, ((Potion *)b)->name);
}
int cmpTrophy(const void *a, const void *b)
{
    /**
     * Function Name: cmpTrophy
     *
     * Purpose:
     *    Compares two trophies based on their names for sorting.
     *
     * Parameters:
     *     const void *a - Pointer to the first trophy.
     *     const void *b - Pointer to the second trophy.
     *
     * Return:
     *     int - Negative if a < b, positive if a > b, zero if equal.
     *
     * Side Effects:
     *     - Compares trophies based on their names using strcmp, 
     *       returns a negative value if the first trophy's name comes before the second trophy's name, 
     *       a positive value if it comes after, and zero if they are equal.
     *     - The function does not modify the input trophies.
     *     - The function does not allocate or reallocate memory.
     *     - The function does not print any output.
     *     - The function does not modify any global variables or data structures.
    */
    return strcmp(((Trophy *)a)->name, ((Trophy *)b)->name);
}
int cmp(const void *a, const void *b)
{
    /**
     * Function Name: cmp
     *
     * Purpose:
     *    Compares two strings for sorting.
     *
     * Parameters:
     *     const void *a - Pointer to the first string.
     *     const void *b - Pointer to the second string.
     *
     * Return:
     *     int - Negative if a < b, positive if a > b, zero if equal.
     *
     * Side Effects:
     *     - Compares strings based on their names using strcmp, 
     *       returns a negative value if the first string comes before the second string, 
     *       a positive value if it comes after, and zero if they are equal.
     *     - The function does not modify the input strings.
     *     - The function does not allocate or reallocate memory.
     *     - The function does not print any output.
     *     - The function does not modify any global variables or data structures.
    */
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcmp(s1, s2);
}

int cmpForRecipe(const void *a, const void *b)
{
    /**
     * Function Name: cmpForRecipe
     *
     * Purpose:
     *    Compares two ingredients for sorting in a potion recipe.
     *
     * Parameters:
     *     const void *a - Pointer to the first ingredient.
     *     const void *b - Pointer to the second ingredient.
     *
     * Return:
     *     int - Negative if a < b, positive if a > b, zero if equal.
     *
     * Side Effects:
     *     - Compares ingredients based on their quantities and names using strcmp, 
     *       returns a negative value if the first ingredient's quantity is less than the second ingredient's quantity,
     *       a positive value if it is greater, and zero if they are equal.
     *       If quantities are equal, compares based on names.
     *     - The function does not modify the input ingredients.
     *     - The function does not allocate or reallocate memory.
     *     - The function does not print any output.
     *     - The function does not modify any global variables or data structures.
    */
    // Compare quantities first, if equal compare names
    if ((*((Ingredient *)a)).quantity == (*((Ingredient *)b)).quantity)
    {
        return strcmp(((Ingredient *)a)->name, ((Ingredient *)b)->name);
    }
    // If quantities are not equal, compare them
    return (*((Ingredient *)b)).quantity - (*((Ingredient *)a)).quantity;
}

Bool is_valid_potion_name_spacing(const char *line, const char *potion_name)
{
    /**
     * Function Name: is_valid_potion_name_spacing
     *
     * Purpose:
     *    Checks if the potion name has valid spacing in the input line.
     *
     * Parameters:
     *     const char *line - The input line containing the potion name.
     *     const char *potion_name - The potion name to check for valid spacing.
     *
     * Return:
     *     Bool - TRUE if the spacing is valid, FALSE otherwise.
     *
     * Side Effects:
     *     - Checks the spacing of the potion name in the input line to ensure it doesn't have multiple spaces between the words.
     *     - The function does not modify the input line or potion name.
     *     - The function does not allocate or reallocate memory.
     *     - The function does not print any output.
     *     - The function does not modify any global variables or data structures.
    */
    const char *start = strstr(line, potion_name);
    if (!start)
        return FALSE;

    for (int i = 0; start[i] != '\0'; i++)
    {
        if (start[i] == ' ')
        {
            if (start[i + 1] == ' ')
            {
                return FALSE;
            }
        }
        if (start[i] == '?' || start[i] == '\0')
            break;
    }

    return TRUE;
}
