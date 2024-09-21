#include "header.h"
int main() {
    srand(time(NULL)); //Cette ligne initialise le générateur de nombres pseudo-aléatoires en utilisant l'heure actuelle comme graine.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //renvoie un handle (un identifiant) pour la console de sortie standard, qui est utilisé pour accéder à cette console.
    SetConsoleOutputCP(CP_UTF8);
    Addcardstozone1();
    int choice;
    while (true) {
        system("cls"); // Elle est  utilisée pour effacer l'écran de la console afin de nettoyer l'affichage avant d'afficher de nouvelles informations.

        print_Zone3();
        printf("\n");
        print_zone2();
        printf("\n");
        // Print the updated deck
        print_cards_zone1();
        printf("\n ");
        printf("\n ");

        printf("1-Move_Card_insideZone1 \n 2-Move_card_fromZone1to2 \n 3-Move_Card_Zone1to3 \n 4-Move_card_Zone2to3\n");
        printf(" 5-Move_card_fromZone2to1 \n 6-resetgame\n 7-quit \n");
        choice = getValidChoice(1, 7);

        switch (choice) {
            case 1:
                move_Card_inside_Zone1();
                break;
            case 2:
                move_cards_zone1to2();
                break;
            case 3:
                move_zone1to3();
                break;
            case 4:
                move_zone2to3();
                break;
            case 5:
                move_cards_zone2to1();
                break;
            case 6:
                Addcardstozone1();
                break;
            case 7:
                printf("end game\n");
                exit(EXIT_SUCCESS);
        }
        if(win_check()){
            printf("-----------------Well played------you won-----------");
            exit(EXIT_SUCCESS);//est utilisé pour arrêter immédiatement l'exécution d'un programme et retourner un code de sortie de 0.
        }
        Sleep(1100); //est une fonction fournie par Windows.h qui est utilisée pour suspendre l'exécution d'un programme pour une durée spécifiée
    }
    return  0;
}

