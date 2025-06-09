#ifndef GLOBALS_H
#define GLOBALS_H

#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LEN 64

//necessary type definitions
typedef enum
{
    FALSE = 0,
    TRUE = 1
} Bool;

typedef enum
{
    SENTENCE,
    QUESTION,
    EXIT
} LineType;

typedef enum
{
    LOOT,
    TRADE,
    BREW,
    LEARN,
    ENCOUNTER,
} Sentence;

typedef enum
{
    INGREDIENT,
    POTION,
    TROPHY,
    ALL_INGREDIENTS,
    ALL_POTIONS,
    ALL_TROPHIES,
    MONSTER,
    POTION_FORMULA,
} Question;

typedef struct
{
    char name[MAX_WORD_LEN];
    int quantity;
} Ingredient;

typedef struct
{
    char name[MAX_WORD_LEN];
    int quantity;
} Potion;

typedef struct
{
    char name[MAX_WORD_LEN];
    int quantity;
} Sign;

typedef struct
{
    char name[MAX_WORD_LEN];
    Sign *signs;
    int sign_count;
    int sign_capacity;

    Potion *potions;
    int potion_count;
    int potion_capacity;
} Monster;

typedef struct
{
    char name[MAX_WORD_LEN];
    int quantity;
} Trophy;

typedef struct
{
    char name[MAX_WORD_LEN];
    Ingredient *ingredients;
    int ingredient_count;
    int ingredient_capacity;
} PotionFormula;

// global variables
extern int last_added_ingredient_index;
extern int last_added_potion_index;
extern int last_added_sign_index;
extern int last_added_monster_index;
extern int last_added_trophy_index;
extern int last_added_formula_index;

extern int ingredient_capacity;
extern int potion_capacity;
extern int trophy_capacity;
extern int sign_capacity;
extern int monster_capacity;
extern int formula_capacity;

extern Ingredient *ingredients;
extern Potion *potions;
extern Trophy *trophies;
extern PotionFormula *formulas;
extern Monster *monsters;
extern Sign *signs;

// utils.c
void remove_trailing_newline(char *line);
void remove_trailing_spaces(char *line);
int split_into_words(char *line, char words[][MAX_WORD_LEN]);
Bool is_alphabetic_custom(const char *token);
Bool is_digit_custom(const char *token);
int cmpIngredient(const void *a, const void *b);
int cmpPotion(const void *a, const void *b);
int cmpTrophy(const void *a, const void *b);
int cmp(const void *a, const void *b);
int cmpForRecipe(const void *a, const void *b);
Bool is_valid_potion_name_spacing(const char *line, const char *potion_name);

// type_detections.c
LineType detect_type(char words[][MAX_WORD_LEN], int word_count);
Sentence detect_sentence(char words[][MAX_WORD_LEN]);
Question detect_question(char words[][MAX_WORD_LEN], int word_count);

// sentence_handle.c
Bool is_valid_ingredient_sentence(char words[][MAX_WORD_LEN], int word_count);
void add_ingredient(Ingredient *ingredients, char *name, int quantity);
Bool is_valid_trade_sentence(char words[][MAX_WORD_LEN], int word_count);
Bool check_valid_trade(Trophy *trophies, Trophy *trophies_to_trade, int trade_index);
void trade(Ingredient *ingredients, Trophy *trophies, Trophy *trophies_to_trade, int num_trophies_to_trade, char words[][MAX_WORD_LEN], int curr_index, int word_count);
Bool is_valid_brew_sentence(char words[][MAX_WORD_LEN], int word_count, const char *line);
Bool has_formula(const char *potion_name, PotionFormula *formulas);
Bool can_brew(const char *potion_name, Ingredient *inventory, PotionFormula *formulas);
void brew_potion(const char *potion_name, Ingredient *inventory, Potion *potions, PotionFormula *formulas);
PotionFormula *get_formula(const char *potion_name, PotionFormula *formulas);
void add_potion(Potion *potions, const char *name);
Bool is_valid_learn_sentence(char words[][MAX_WORD_LEN], int word_count, const char *line);
Bool learn_potion_formula(char words[][MAX_WORD_LEN], int word_count, PotionFormula *formulas);
Bool learn_effectiveness(char words[][MAX_WORD_LEN], int word_count, Monster *monsters);
Bool is_valid_encounter_sentence(char words[][MAX_WORD_LEN], int word_count);
void handle_encounter(char words[][MAX_WORD_LEN], int word_count, Monster *monsters, Potion *potions, Trophy *trophies);

// question_handle.c
void handle_specific_ingredient_query(char words[][MAX_WORD_LEN], int word_count);
void handle_specific_potion_query(char words[][MAX_WORD_LEN], int word_count, const char *line);
void handle_specific_trophy_query(char words[][MAX_WORD_LEN], int word_count);
void handle_all_ingredients_query();
void handle_all_potions_query();
void handle_all_trophies_query();
void handle_monster_query(char words[][MAX_WORD_LEN], int word_count);
void handle_potion_recipe_query(char words[][MAX_WORD_LEN], int word_count, const char *line);

//capacity_ensuring.c
void ensure_ingredient_capacity();
void ensure_potion_capacity();
void ensure_trophy_capacity();
void ensure_monster_capacity();
void ensure_formula_capacity();
void ensure_sign_capacity();
void ensure_monster_sign_capacity(Monster *m);
void ensure_monster_potion_capacity(Monster *m);

#endif