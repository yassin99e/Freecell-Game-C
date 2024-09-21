#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#define FOREGROUND_BLACK 0
#define BACKGROUND_WHITE BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE

typedef struct card {
    char *rank;
    char *suit;
    struct card *next;
    struct card *prev;
} Card;

char *suits[] = {"\u2665", "\u2666", "\u2663", "\u2660"}; //représente le symbole Unicode des logos des cartes.
char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

Card *Zone1[8];
Card *Zone2[4];
Card *Zone3[4];

int zone1[8];
int zone2[4];
int zone3[4];

void initializeVariables() {
    int i;
    for (i = 0; i < 8; i++) {
        Zone1[i] = NULL;
        zone1[i] = 0;
        if (i < 4) {
            Zone2[i] = NULL;
            Zone3[i] = NULL;
            zone2[i] = 0;
            zone3[i] = 0;
        }
    }
}

Card *createCard(int SuitIndex, int RankIndex) {
    Card *newcard = (Card *)malloc(sizeof(Card));
    newcard->rank=ranks[RankIndex];
    newcard->suit=suits[SuitIndex];
    newcard->next=NULL;
    newcard->prev=NULL;
    return newcard;
}

void swapCards(Card **deck, int i, int j) {
    Card *temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
}

void shuffleDeck(Card **deck, int deckSize) {
    int i,j;
    for (i = deckSize - 1; i > 0; i--) {
        j = rand() % (i + 1); //generer un nombre aleatoire entre 0 et i+1
        swapCards(deck, i, j); //permuter le contenu de la case i avec la case j.
    }
}

Card **generateFullDeck() {
    Card **allCards = (Card **)malloc(52 * sizeof(Card *));
    int i = 0;
    int suitIndex,rankIndex;

    for (suitIndex = 0; suitIndex < 4; suitIndex++) {
        for (rankIndex = 0; rankIndex < 13; rankIndex++) {
            allCards[i++]=createCard(suitIndex, rankIndex);
        }
    }
    // Shuffle the deck
    shuffleDeck(allCards, 52);
    return allCards;
}

void SetCardColorsBySuit(const char *suit) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set background color to white
    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

    // Set font color based on suit
    if (strcmp(suit, "\u2665") == 0 || strcmp(suit, "\u2666") == 0) {
        // Hearts or Diamonds, set font color to red and background color to white
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_WHITE);
    } else {
        // Clubs or Spades, set font color to black and background color to white
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLACK | BACKGROUND_WHITE);
    }
}

void Print_Card(Card *C) {
    if (C != NULL) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Set colors based on card suit
        SetCardColorsBySuit(C->suit);

        if(strcmp(C->rank,"10")==0){
            printf("%s   %s ", C->rank, C->suit);
        }
        else{
            printf("%s    %s ", C->rank, C->suit);
        }
        // Reset colors to default
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        // Print an empty space for NULL cards
        printf("         ");
    }
}

void Empiler(Card **Pile, Card *card) {
    if (*Pile == NULL) {
        card->next=NULL;
        card->prev=NULL;
        *Pile = card;
    } else {
        card->next = *Pile;
        (*Pile)->prev = card;
        card->prev = NULL;  // pour s'assurer que le champ prev de la carte déplacée est NULL
        *Pile = card;
    }
}

void Addcardstozone1() {
    initializeVariables();
    Card **Allcards = generateFullDeck();
    int i = 0, j, k;

    // Fill the first four columns with 7 cards each
    for (j = 0; j < 4; j++) {
        for (k = 0; k < 7; k++) {
            Empiler(&Zone1[j], Allcards[i]);
            i++;
            zone1[j]++;
        }
    }

    // Fill the last four columns with 6 cards each
    for (j = 4; j < 8; j++) {
        for (k = 0; k < 6; k++) {
            Empiler(&Zone1[j], Allcards[i]);
            i++;
            zone1[j]++;
        }
    }
}


void print_cards_zone1(){
    printf("-------------------Zone1-------------------------\n");
    int i;
    for(i=0;i<8;i++){
        if(Zone1[i]!=NULL){
            Card *P=Zone1[i];
            while(P->next!=NULL)
                P=P->next;
            printf("\n");
            printf("col %d : ",i+1);
            while(P!=NULL){
                Print_Card(P);
                printf(" ");
                P=P->prev;
            }
            printf("\n");
        }
        else{
            printf("col %d : ",i+1);
            printf("empty case \n");
        }
    }
}

void Depiler(Card **Pile) {
    if (*Pile != NULL) {
        *Pile = (*Pile)->next;
        // Update the prev pointer of the new top card
        if (*Pile != NULL) {
            (*Pile)->prev = NULL;//pour eviter une fuite de memoire
        }
    }
}

bool ismove_valid(Card *source,Card *dest){
    if(source==NULL)
        return false;
    if(dest==NULL)
        return true;
    if(((strcmp(source->rank,"Q")==0 && strcmp(dest->rank,"K")==0) ||
        (strcmp(source->rank,"J")==0 && strcmp(dest->rank,"Q")==0) ||
        (strcmp(source->rank,"10")==0 && strcmp(dest->rank,"J")==0) ||
        (atoi(dest->rank)-atoi(source->rank)==1)
        ) &&
       (
        ((strcmp(source->suit,"\u2665")==0 || strcmp(source->suit,"\u2666")==0) &&
        ((strcmp(dest->suit,"\u2663")==0 || strcmp(dest->suit,"\u2660")==0))) ||
        ((strcmp(source->suit,"\u2663")==0 || strcmp(source->suit,"\u2660")==0) &&
        ((strcmp(dest->suit,"\u2665")==0 || strcmp(dest->suit,"\u2666")==0)))
        )
       )
        return true;
    else
        return false;
}

void move_Card_inside_Zone1(){
    int source,dest;
    while(true){
        printf(" \n la source  : \n");
        if(scanf("%d",&source)==1){ //scanf retourne le nombre d'elements lus avec succes
            break;
        }
        else
            printf("donner une valeur entier");
    }
    while(true){
        printf(" \n la destination  : \n");
        if(scanf("%d",&dest)==1){
            break;
        }
        else
            printf("donner une valeur entier");
    }
    if(source<1 || source>8 || dest<1 || dest>8){
        printf("Erreur Index \n");
        return ;
    }
    if(!ismove_valid(Zone1[source-1],Zone1[dest-1])){
        printf("movement invalide \n");
        return ;
    }
    Card *card=Zone1[source-1];
    Depiler(&Zone1[source-1]);
    Empiler(&Zone1[dest-1],card);
    zone1[source-1]--;
    zone1[dest-1]++;
}

 void print_zone2(){
     int i;
     printf("------------------- ZONE2---------------------\n");
     for(i=0;i<4;i++){
        if(Zone2[i]==NULL)
            printf("Empty case \t\t\t");
        else{
            Print_Card(Zone2[i]);
            printf("\t\t\t");
        }
     }
 }

 void move_cards_zone1to2(){
     int source,dest;
     while(true){
        printf(" \n la source  : \n");
        if(scanf("%d",&source)==1){
            break;
        }
        else
            printf("donner une valeur entier");
    }
    while(true){
        printf(" \n la destination  : \n");
        if(scanf("%d",&dest)==1){
            break;
        }
        else
            printf("donner une valeur entier");
    }
    if(source<1 || source>8 || dest<1 || dest>4){
        printf("Erreur Index \n");
        return ;
    }
    if(Zone1[source-1]==NULL || Zone2[dest-1]!=NULL){
        printf("mouvement invalide ");
        return ;
    }
    Card *card=Zone1[source-1];
    Depiler(&Zone1[source-1]);
    Zone2[dest-1]=card;
    zone1[source-1]--;
    zone2[dest-1]++;
 }

void move_cards_zone2to1(){
     int source,dest;
     while(true){
        printf(" \n la source  : \n");
        if(scanf("%d",&source)==1){
            break;
        }
        else
            printf("donner une valeur entier");
    }
    while(true){
        printf(" \n la destination  : \n");
        if(scanf("%d",&dest)==1){
            break;
        }
        else
            printf("donner une valeur entier");
    }
    if(source<1 || source>4 || dest<1 || dest>8){
        printf("Erreur Index \n");
        return ;
    }
    if(!ismove_valid(Zone2[source-1],Zone1[dest-1])){
        printf("movement invalide \n");
        return ;
    }
    Empiler(&Zone1[dest-1],Zone2[source-1]);
    Zone2[source-1]=NULL;
    zone2[source-1]--;
    zone1[dest-1]++;
 }

void print_Zone3(){
    printf("--------------------Zone3----------------\n");
    int i;
    for(i=0;i<4;i++){
        if(Zone3[i]==NULL)
            printf("Empty case \t\t\t");
        else{
            Print_Card(Zone3[i]);
            printf("\t\t\t");
        }
    }
}

bool is_move_valid_1or2to3(Card *source,Card *dest){
    if(source==NULL)
        return false;
    if(dest==NULL && strcmp(source->rank,"A")==0)
        return true;
    if(dest!=NULL && (strcmp(source->suit,dest->suit)==0) &&
       ((atoi(source->rank)-atoi(dest->rank)==1) ||
        (strcmp(source->rank,"K")==0 && strcmp(dest->rank,"Q")==0) ||
        (strcmp(source->rank,"Q")==0 && strcmp(dest->rank,"J")==0) ||
        (strcmp(source->rank,"J")==0 && strcmp(dest->rank,"10")==0) ||
        (strcmp(source->rank,"2")==0 && strcmp(dest->rank,"A")==0)
        )
       )
        return true;
    else
        return false;
}

void move_zone1to3(){
    int source,dest;
     while(true){
        printf(" \n la source  : \n");
        if(scanf("%d",&source)==1){
            break;
        }
        else
            printf("donner une valeur entier");
    }
    while(true){
        printf(" \n la destination  : \n");
        if(scanf("%d",&dest)==1){
            break;
        }
        else
            printf("donner une valeur entier");
    }
    if(source<1 || source>8 || dest<1 || dest>4){
        printf("Erreur Index \n");
        return ;
    }
    if(!is_move_valid_1or2to3(Zone1[source-1],Zone3[dest-1])){
        printf("Erreur mouvement! \n");
        return ;
    }
    Card *card=Zone1[source-1];
    Depiler(&Zone1[source-1]);
    Empiler(&Zone3[dest-1],card);
    zone1[source-1]--;
    zone3[dest-1]++;
}

void move_zone2to3(){
    int source,dest;
    while(true){
        printf(" \n la source  : \n");
        if(scanf("%d",&source)==1){
            break;
        }
        else
            printf("donner une valeur entier");
    }
    while(true){
        printf(" \n la destination  : \n");
        if(scanf("%d",&dest)==1){
            break;
        }
        else
            printf("donner une valeur entier");
    }
    if(source<1 || source>4 || dest<1 || dest>4){
        printf("Erreur Index \n");
        return ;
    }
    if(!is_move_valid_1or2to3(Zone2[source-1],Zone3[dest-1])){
        printf("Erreur mouvement! \n");
        return ;
    }
    Empiler(&Zone3[dest-1],Zone2[source-1]);
    Zone2[source-1]=NULL;
    zone2[source-1]--;
    zone3[dest-1]++;
}

int getValidChoice(int min, int max) {
    int choice;
    while (1) {
        printf("Enter a number between %d and %d: ", min, max);
        if (scanf("%d", &choice) == 1) {
            if (choice >= min && choice <= max) {

                return choice;
            } else {
                printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
            }
        } else {
            // Input is not an integer, clear the input buffer
            while (getchar() != '\n');
            printf("Invalid input. Please enter a valid integer.\n");
        }
    }
}

bool win_check(){
    bool z1=true,z2=true,z3=true;
    int i;
    for(i=0;i<8;i++){
        if(zone1[i]!=0)
            z1=false;
        if(i<4){
            if(zone2[i]!=0)
                z2=false;
            if(zone3[i]!=13)
                z3=false;
        }
    }
    if(z1 && z2 && z3)
        return true;
    else
        return false;
}

