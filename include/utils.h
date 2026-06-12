#ifndef UTILS_H
#define UTILS_H

#include "gamelib.h"

// Macro che indica la versione del gioco
#define game_version "v1.1.1"

// Colori per le scritte colorate in gioco.
#define RESET       "\033[0m"
#define ROSSO       "\033[31m"
#define VERDE       "\033[32m"
#define H_YELLOW    "\033[33m"
#define CIANO       "\033[36m"
#define ROSA        "\033[95m"


#define t_length 130
#define player_name_length 20

#define len(arr) sizeof(arr) / sizeof(arr[0])
#define lenum(enum_name) enum_name##_length
#define randint(n) (rand() % (n))

#define enemy_exists(giocatore) ((giocatore)->mondo == 0 ? (giocatore)->pos_mondoreale->nemico > 0 : (giocatore)->pos_soprasotto->nemico > 0)
#define item_exists(giocatore) ((giocatore)->pos_mondoreale->oggetto > 0)

#define enemy_selector(giocatore) ((giocatore)->mondo == 0 ? (giocatore)->pos_mondoreale->nemico : (giocatore)->pos_soprasotto->nemico)
#define player_zone_position(giocatore) ((giocatore)->mondo == 0 ? (giocatore)->pos_mondoreale->id_zona : (giocatore)->pos_soprasotto->id_zona)
#define player_world_position(giocatore) ((giocatore)->mondo == 0 ? (giocatore)->pos_mondoreale : (giocatore->pos_soprasotto))

#define get_nome_mondo(giocatore) ((giocatore)->mondo == 0 ? ("Mondo Reale") : ("Sopra-Sotto"))

// Funzioni utili
void nuke_buffer();
void terminal_redimensioner(int width, int height);
void terminal_cleaner();
void game_title_printer();
void printf_centered(const char* color, const char* text, ...);
void wait_4click(const char* text);
void player_abilities(giocatore* player, const char* msg);
void player_abilities_centered(giocatore* player, const char* msg, const char* color);

char* order_color(const uint8_t p_order, const uint8_t p_id);


// Funzioni Helper per trasformare gli enum in gamelib.h in stringhe
const char* get_nome_zona(uint8_t zona);
const char* get_nome_nemico(uint8_t nemico);
const char* get_nome_oggetto(uint8_t oggetto);
const char* get_descrizione_inventario(uint8_t oggetto);

// Persistenza vincitori
void salva_vincitore(const char* nome);
void stampa_vincitori();


#endif