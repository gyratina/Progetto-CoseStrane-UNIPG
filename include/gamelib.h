#ifndef GAMELIB_H
#define GAMELIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


void imposta_gioco();
void gioca();
void termina_gioco();
void crediti();

struct zona_mondoreale;
struct zona_soprasotto;


typedef enum tipo_zona{
    bosco,
    scuola,
    laboratorio,
    caverna,
    strada,
    giardino,
    supermercato,
    centrale_elettrica,
    deposito_abbandonato,
    stazione_polizia,
    tipo_zona_length
} tipo_zona;

typedef enum tipo_nemico{
    nessun_nemico,
    billi,
    democane,
    demotorzone,
    tipo_nemico_length
} tipo_nemico;

typedef enum tipo_oggetto{
    nessun_oggetto,
    bicicletta,
    maglietta_fuocoinferno,
    bussola,
    schitarrata_metallica,
    antenna_radio,
    tipo_oggetto_length
} tipo_oggetto;


typedef struct nemico {
    tipo_nemico tipologia;

    int attacco_psichico;
    int difesa_psichica;
} nemico;

typedef struct giocatore {
    char* nome;  // Puntatore dinamico per fare nome in array dinamico calloc()
    uint8_t mondo;   // 0 = Mondoreale | 1 = Soprasotto

    struct zona_mondoreale* pos_mondoreale;     // variabile che punta alla zona del mondoreale dove si trova il giocatore se mondo = 0
    struct zona_soprasotto* pos_soprasotto;     // variabile che punta alla zona del soprasotto dove si trova il giocatore se mondo = 1

    int attacco_psichico;
    int difesa_psichica;
    int fortuna;

    int durata_buff_att;
    int durata_buff_dif;

    tipo_oggetto zaino[3];
} giocatore;

typedef struct zona_mondoreale{
    tipo_zona zona;
    tipo_nemico nemico;
    tipo_oggetto oggetto;

    struct zona_mondoreale* avanti;
    struct zona_mondoreale* indietro;
    struct zona_soprasotto* link_soprasotto;
    
    uint8_t id_zona;
} zona_mondoreale;

typedef struct zona_soprasotto{
    tipo_zona zona;
    tipo_nemico nemico;

    struct zona_soprasotto* avanti;
    struct zona_soprasotto* indietro;
    struct zona_mondoreale* link_mondoreale;

    uint8_t id_zona;
} zona_soprasotto;


#endif