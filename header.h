#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#define FOREGROUND_BLACK 0
#define BACKGROUND_WHITE BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE

typedef struct card {
    char *rank;
    char *suit;
    struct card *next;
    struct card *prev;
} Card;

void initializeVariables();
Card *createCard(int SuitIndex, int RankIndex);
void swapCards(Card **deck, int i, int j);
void shuffleDeck(Card **deck, int deckSize);
Card **generateFullDeck();
void SetCardColorsBySuit(const char *suit);
void Print_Card(Card *C);
void Empiler(Card **Pile, Card *card);
void Addcardstozone1();
void print_cards_zone1();
void Depiler(Card **Pile);
bool ismove_valid(Card *source,Card *dest);
void move_Card_inside_Zone1();
void print_zone2();
void move_cards_zone1to2();
void move_cards_zone2to1();
void print_Zone3();
bool is_move_valid_1or2to3(Card *source,Card *dest);
void move_zone1to3();
void move_zone2to3();
int getValidChoice(int min, int max);
bool win_check();
#endif // FONCTION_H_INCLUDED

