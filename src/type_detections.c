#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

LineType detect_type(char words[][MAX_WORD_LEN], int word_count)
{
    /**
        * Function Name: detect_type
        *
        * Purpose:
        *    Detects the type of the input line based on the first word and the last word.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int word_count - The number of words in the input line.
        *
        * Return:
        *     LineType - The type of the input line.
        *
        * Side Effects:
        *    - Detects the type of the input line based on the first word and the last word.
        *    - The function does not modify any global variables or data structures.
        *    - The function does not allocate or reallocate memory.
        *    - The function does not print any output.
        *    - Returns EXIT if the input line is "Exit".
        *    - Returns QUESTION if the last word ends with a '?', validity check later.
        *    - Returns SENTENCE otherwise, the validity of the sentence will be checked later.
     */
    if (word_count == 1 && strcmp(words[0], "Exit") == 0)
    {
        return EXIT;
    }

    char *last_word = words[word_count - 1];
    int len = strlen(last_word);
    if (len > 0 && last_word[len - 1] == '?')
    {
        return QUESTION;
    }

    return SENTENCE;
}

Sentence detect_sentence(char words[][MAX_WORD_LEN])
{
    /**
        * Function Name: detect_sentence
        *
        * Purpose:
        *    Detects the type of the input sentence based on the first word and the second word.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *
        * Return:
        *     Sentence - The type of the input sentence.
        *
        * Side Effects:
        *    - Detects the type of the input sentence based on the second word.
        *    - If it doesn't match any known sentence types, it returns -1.
        *    - The function does not check the validity of the sentence, it will be checked later.
        *    - The function does not modify any global variables or data structures.
        *    - The function does not allocate or reallocate memory.
        *    - The function does not print any output.
     */
    if (strcmp(words[1], "loots") == 0)
    {
        return LOOT;
    }
    else if (strcmp(words[1], "trades") == 0)
    {
        return TRADE;
    }
    else if (strcmp(words[1], "brews") == 0)
    {
        return BREW;
    }
    else if (strcmp(words[1], "learns") == 0)
    {
        return LEARN;
    }
    else if (strcmp(words[1], "encounters") == 0)
    {
        return ENCOUNTER;
    }

    return -1;
}

Question detect_question(char words[][MAX_WORD_LEN], int word_count)
{
    /**
        * Function Name: detect_question
        *
        * Purpose:
        *    Detects the type of the input question based on the first word and the second word.
        *
        * Parameters:
        *     char words[][MAX_WORD_LEN] - The array of words from the input line.
        *     int word_count - The number of words in the input line.
        *
        * Return:
        *     Question - The type of the input question.
        *
        * Side Effects:
        *    - Detects the type of the input question based on the first word and the second word.
        *    - If it doesn't match any known question types, it returns -1.
        *    - The function checks the validity because all types are hardcoded except the spacing of the potion name.
        *    - The function does not modify any global variables or data structures.
        *    - The function does not allocate or reallocate memory.
        *    - The function does not print any output.
     */
    if (word_count < 3 || strcmp(words[word_count - 1], "?") != 0)
    {
        return -1;
    }

    if (strcmp(words[0], "Total") == 0)
    {
        if (strcmp(words[1], "ingredient") == 0)
        {
            //if the first word is "Total" and the second word is "ingredient" and no other words it is a all ingredient query
            if (word_count == 3)
                return ALL_INGREDIENTS;
            //if the first word is "Total" and the second word is "ingredient" and there is one other word it is a specific ingredient query
            else if (word_count == 4)
            {
                if (!is_alphabetic_custom(words[2]))
                {
                    return -1;
                }
                return INGREDIENT;
            }
            //no other valid types starting with Total ingredient
            else
            {
                return -1;
            }
        }
        else if (strcmp(words[1], "potion") == 0)
        {
            //if the first word is "Total" and the second word is "potion" and no other words it is a all potion query
            if (word_count == 3)
                return ALL_POTIONS;
            //if the first word is "Total" and the second word is "potion" and there are other words it is a specific potion query
            else if (word_count > 3)
            {
                for (int i = 2; i < word_count - 1; i++)
                {
                    if (!is_alphabetic_custom(words[i]))
                    {
                        return -1;
                    }
                }
                return POTION;
            }
            //no other valid types starting with Total potion
            else
            {
                return -1;
            }
        }
        else if (strcmp(words[1], "trophy") == 0)
        {
            //if the first word is "Total" and the second word is "trophy" and no other words it is a all trophy query
            if (word_count == 3)
                return ALL_TROPHIES;
            //if the first word is "Total" and the second word is "trophy" and there is one other word it is a specific trophy query
            else if (word_count == 4)
            {
                if (!is_alphabetic_custom(words[2]))
                {
                    return -1;
                }
                return TROPHY;
            }
            //no other valid types starting with Total trophy
            else
            {
                return -1;
            }
        }
        //no other valid types starting with Total
        else
        {
            return -1;
        }
    }
    else if (strcmp(words[0], "What") == 0 && strcmp(words[1], "is") == 0)
    {
        //if the start is "What is effective against" and there are 6 words (because monster names are one-worded)
        if (word_count == 6 &&
            strcmp(words[2], "effective") == 0 &&
            strcmp(words[3], "against") == 0)
        {
            if (!is_alphabetic_custom(words[4]))
            {
                return -1;
            }
            return MONSTER;
        }
        //if the start is "What is in" if it has more than 5 words it is a potion formula query
        else if (word_count >= 5 && strcmp(words[2], "in") == 0)
        {
            if (word_count - 3 < 1)
            {
                return -1;
            }

            for (int i = 3; i < word_count - 1; i++)
            {
                if (!is_alphabetic_custom(words[i]))
                {
                    return -1;
                }
            }
            return POTION_FORMULA;
        }
        //no other valid types starting with What is
        else
        {
            return -1;
        }
    }
    //no other valid type
    return -1;
}
