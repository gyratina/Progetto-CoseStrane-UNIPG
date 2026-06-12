#include "utils.h"
#include "gamelib.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iso646.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    time_t t;
    srand((unsigned) time(&t));
    
    terminal_redimensioner(t_length, 40);
    game_title_printer();
    wait_4click("Premi INVIO.");
    game_title_printer();

    uint8_t choice;
    do {
        game_title_printer();

        //printf_centered("SCEGLI UNA OPZIONE.\n", ROSSO, t_length);
        printf_centered(ROSSO, "[1]  Impostazioni Partita.\n");
        printf_centered(ROSSO, "[2]  Inizia Partita.\n");
        printf_centered(ROSSO, "[3]  Torna al desktop.\n");
        printf_centered(ROSSO, "[4]  Visualizza i Crediti.\n");

        scanf("%hhu", &choice);
        nuke_buffer();
        switch(choice) {
            case 1:
                imposta_gioco();
                break;
            
            case 2:
                gioca();
                break;

            case 3:
                termina_gioco();
                break;
            
            case 4:
                crediti();
                break;

            default:
                terminal_cleaner();
                game_title_printer();

                printf_centered(RESET, "L'opzione scelta non è valida o non esiste.\n");
                printf_centered(RESET, "Riprovare.\n");
                sleep(1);

                terminal_cleaner();
                game_title_printer();
                wait_4click("Premi INVIO.");
                break;
        }

    } while(choice != 3);
}