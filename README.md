# Decodifica Algoritmica Avanzata - Cifrario di Cesare Variabile

Questo progetto implementa un sistema di decrittazione per una variante complessa del Cifrario di Cesare, progettato per risolvere testi cifrati con spostamenti non uniformi.

## Il Problema: Complessità Esponenziale
A differenza del cifrario di Cesare standard (dove lo shift è uguale per tutto il testo), in questa variante **ogni singola lettera** può essere stata spostata indipendentemente di +1 o -1. 

Questo genera un numero di combinazioni pari a $2^n$ (dove *n* è il numero di lettere), rendendo la decodifica manuale o per forza bruta semplice impossibile per frasi lunghe.

## Soluzione Tecnologica
Per risolvere il problema in frazioni di secondo, il software utilizza:
- **Validazione Lessicale**: Un dizionario di oltre 660.000 termini italiani.
- **Hash Table**: Una struttura dati ottimizzata per ricerche istantanee, fondamentale per setacciare migliaia di combinazioni al secondo.
- **Algoritmo di Ricostruzione**: Il programma identifica l'unico percorso logico che trasforma i caratteri in parole di senso compiuto.

## Contenuto del Repository
- `decifrario_cesare.cpp`: Il software di decodifica (core).
- `test.cpp`: Utility per generare testi cifrati e testare l'algoritmo.
- `660000_parole_italiane.txt`: Database lessicale di supporto.
- `testo.txt`: Esempio di input cifrato.

## Come testare il progetto
Per comodità, è disponibile un pacchetto pre-configurato nella sezione **Releases**.
1. Scarica lo ZIP e estrailo.
2. Esegui `test.exe` per creare un messaggio cifrato.
3. Esegui `decifrario.exe` per vedere l'algoritmo ricostruire il testo originale in tempo reale.
