# Progetto "Cose Strane"
**Cose Strane** è un'avventura testuale RPG a turni sviluppata in C. Il progetto esplora concetti complessi di programmazione procedurale, gestione dinamica della memoria e strutture dati non lineari, traendo ispirazione dall'immaginario di *Stranger Things*.

- Anno: 2026<br>
- Autori:
  - <a href="https://francescosantini.sites.dmi.unipg.it/index.html">Francesco Santini</a>, Docente e direttore artistico del progetto. Ha dettato numerose indicazioni architetturali.
  - <a href="https://valerioditommaso.dev">Valerio Di Tommaso</a>, Studente (io) e programmatore del progetto e responsabile dell'implementazione concreta dell'architettura. Direttore artistico del sistema di combattimento e della TUI.

_Title Screen:_
<img width="2204" height="1838" alt="immagine" src="https://github.com/user-attachments/assets/f2179d10-6eaa-477c-aace-78861abea8b6" />

---

## Architettura del Software

Il progetto segue un approccio modulare per separare la logica di gioco, le strutture dati e le utility di sistema.

### 1. Gestione della Memoria e Strutture Dati
Il cuore del gioco risiede nella rappresentazione spaziale dei due mondi (Mondo Reale e Sopra-Sotto).

#### Mappa Duale (Linked Lists)
Le zone sono implementate come **liste doppiamente concatenate speculari**.
- **Strutture:** `struct zona_mondoreale` e `struct zona_soprasotto`.
- **Collegamenti Orizzontali:** Ogni nodo punta a `avanti` e `indietro`, permettendo una navigazione bidirezionale.
- **Collegamenti Verticali:** Ogni zona del Mondo Reale possiede un puntatore `link_soprasotto` alla sua controparte dimensionale, e viceversa.
- **Allocazione:** Tutte le zone sono allocate dinamicamente tramite `calloc` per garantire l'azzeramento della memoria e prevenire comportamenti indefiniti.

#### Gestione Dinamica dei Giocatori
- I giocatori sono gestiti tramite un array di puntatori `static giocatore* giocatori[4]`.
- Il nome del giocatore è un puntatore a `char` allocato dinamicamente con `realloc` durante la fase di personalizzazione (es. attivazione dello status "UndiciVirgolaCinque").

### 2. Ciclo di Gioco e State Machine
Il gioco opera su un loop principale (`gioca()`) che gestisce una macchina a stati finiti:

- **Fase di Inizializzazione:** Setup dei dadi (seed con `time(NULL)`), allocazione giocatori e generazione mappa.
- **Ciclo dei Turni:** All'inizio di ogni ciclo, l'ordine dei giocatori viene rimescolato casualmente per garantire dinamicità.
- **Gestione Stato Giocatore:** Lo stato include la posizione dimensionale (`mondo`), l'inventario (array di enum `tipo_oggetto`), e i buff temporanei (`durata_buff_att/dif`) che decadono ad ogni ciclo.

### 3. Logica del Game Master (GM Menu)
Il menu GM permette la manipolazione "a caldo" della struttura dati della mappa:
- **Inserimento/Cancellazione:** Algoritmi di "ricucitura" dei puntatori per inserire o rimuovere nodi in qualsiasi posizione della lista, mantenendo l'integrità dei collegamenti speculari tra le due dimensioni.
- **Validazione Mappa:** Prima di iniziare, il sistema esegue una scansione completa (`chiudi_mappa()`) per verificare:
    - Presenza di almeno 15 zone.
    - Esistenza di esattamente un boss (**Demotorzone**) nel Sopra-Sotto.
    - Correttezza dei collegamenti bidirezionali.

### 4. Sistema di Combattimento e Probabilità
Il combattimento è governato da statistiche psichiche:
- **Calcolo Danni:** Basato sul confronto tra `attacco_psichico` del giocatore/nemico e `difesa_psichica` dell'avversario, modulato da fattori di fortuna e roll casuali.
- **Meccanica Dimensionale:** Il passaggio al Sopra-Sotto è deterministico dal Mondo Reale, ma il ritorno richiede un test sulla statistica `fortuna` (roll < fortuna).

---

## Dettagli Implementativi

### Interfaccia Utente (UI)
Sebbene sia un gioco testuale, l'esperienza è arricchita tramite:
- **Sequenze di Escape ANSI:** Gestione dei colori (`\033[...]`) e manipolazione del cursore.
- **Terminal Control:** Ridimensionamento forzato della finestra tramite sequenze escape e pulizia selettiva dello schermo.
- **Buffered I/O:** Utilizzo di `nuke_buffer()` per gestire in modo robusto gli input sporchi dello `scanf` e prevenire loop infiniti o skip di menu.

### Modularità dei File
- `gamelib.c / .h`: Incapsula la logica di business e le definizioni delle strutture dati. Utilizza variabili `static` per nascondere lo stato interno della mappa (information hiding).
- `utils.c / .h`: Contiene primitive di sistema, wrapper per la stampa formattata e funzioni helper per la conversione di `enum` in stringhe (pattern *stringification*).
- `main.c`: Orchestratore di alto livello e gestore del menu radice.

---

## Requisiti Tecnici e Compilazione

Il codice aderisce agli standard C moderni (C99/C11) e richiede il link alla libreria standard.

**Compilazione consigliata:**
```bash
gcc -o build/CoseStrane src/*.c -std=c11 -Wall -Wextra -Iinclude -O2
```

---

## 🛡️ Sicurezza e Robustezza
- **Memory Leak:** Il progetto include una funzione `dealloca_mappe()` che esegue il crawling completo delle liste concatenate per liberare ogni nodo prima della chiusura o rigenerazione della mappa.
- **Input Validation:** Ogni input utente è filtrato tramite cicli `do-while` e controlli sui range degli enum.
