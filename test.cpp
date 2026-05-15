#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <cstdlib>

using namespace std;

// Funzione che codifica un singolo carattere
char encode_char(char c, bool move_next) {
    if (!isalpha(c)) return c; // Mantieni punteggiatura e spazi

    char result;
    if (move_next) {
        result = c + 1;
        // Gestione rotazione (se dopo la 'z' o 'Z')
        if (c == 'z') result = 'a';
        if (c == 'Z') result = 'A';
    } else {
        result = c - 1;
        // Gestione rotazione (se prima di 'a' o 'A')
        if (c == 'a') result = 'z';
        if (c == 'A') result = 'Z';
    }
    return result;
}

string encode_phrase(string phrase) {
    string encoded = "";

    // Inizializziamo il seed per il generatore casuale
    srand(time(NULL));

    for (char c : phrase) {
        if (isalpha(c)) {
            // Sceglie casualmente 0 (precedente) o 1 (successiva)
            bool choice = rand() % 2;
            encoded += encode_char(c, choice);
        } else {
            encoded += c; // Lascia invariati spazi e punteggiatura
        }
    }
    return encoded;
}

int main() {
    string input;

    cout << "Inserisci la frase da codificare: ";
    getline(cin, input);

    if (input.empty()) {
        return 0;
    }

    string output = encode_phrase(input);

    cout << "Frase originale: " << input << endl;
    cout << "Frase codificata: " << output << endl;

    return 0;
}
