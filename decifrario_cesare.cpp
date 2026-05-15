#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

using namespace std;

typedef struct node
{
    string word;
    struct node *next;
}
node;

const unsigned int N = (26 * 26);

// Hash table
node *table[N];

unsigned int hash_func(const string word)
{
    // Correzione minima: evita crash se la parola è più corta di 2 caratteri
    if (word.length() < 2)
    {
        return (toupper(word[0]) - 'A');
    }
    return (toupper(word[0]) - 'A') * 26 + (toupper(word[1]) - 'A');
}

// Returns true if word is in dictionary, else false
bool check(const string word)
{
    node *ptr = table[hash_func(word)];
    while (ptr != NULL)
    {
        if (word == ptr->word)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful, else false
void unload_help(node *ptr)
{
    if (ptr->next == NULL)
    {
        delete ptr;
        return;
    }
    unload_help(ptr->next);
    delete ptr;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            unload_help(table[i]);
            table[i] = NULL;
        }
    }
    return true;
}

bool load(const string dictionary)
{
    ifstream dict(dictionary);
    if (!dict)
    {
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    string word;
    while (getline(dict, word)){
        int i = hash_func(word);
        node *n = new node;
        if (n == NULL)
        {
            unload();
            return false;
        }
        n->word = word;
        n->next = table[i];
        table[i] = n;
    }
    dict.close();
    return true;
}

string make_prev(string word){
    string prev_chars = "";
    for (int i = 0, len = word.length(); i < len; i++){
        if (isalpha(word[i]) == 0){
            continue;
        }
        char c = word[i] - 1;
        if (isalpha(c) == 0){
            c += 26;
        }
        prev_chars += c;
    }
    return prev_chars;
}

string make_next(string word){
    string next_chars = "";
    for (int i = 0, len = word.length(); i < len; i++){
        if (isalpha(word[i]) == 0){
            continue;
        }
        char c = word[i] + 1;
        if (isalpha(c) == 0){
            c -= 26;
        }
        next_chars += c;
    }
    return next_chars;
}

string spell_check(string word){
    string prev = make_prev(word);
    string next = make_next(word);
    string result = "[Not found]";
    int N_len = word.length();
    int numCombinations = 1 << N_len;
    for (int i = 0; i < numCombinations; i++) {
        string temp = "";
        for (int j = N_len - 1; j >= 0; j--) {
            if ((i>>j)%2){
                temp += prev[N_len-1-j];
            }
            else{
                temp += next[N_len-1-j];
            }
        }
        if(check(temp)){
            result = temp;
            break;
        }
    }
    return result;
}

int main(void)
{
    string dictionary = "660000_parole_italiane.txt";
    bool loaded = load(dictionary);
    if (!loaded)
    {
        cout << "Could not load dictionary " << dictionary << endl;
        return 1;
    }
    string text = "testo.txt";
    ifstream file(text);
    if (!file)
    {
        cout << "Could not open text file." << text << endl;
        unload();
        return 1;
    }

    string words, word, result = "";
    unsigned int i = 0;

    while (getline(file, words))
    {
        if (words == "\n" || words.empty()){
            continue;
        }

        words.erase(0, words.find_first_not_of(" \t\r\n"));
        words.erase(words.find_last_not_of(" \t\r\n") + 1);

        int counter = count(words.begin(), words.end(), ' ');
        for (int j = 0; j <= counter; j++){
            i = words.find(" ");
            if (i != string::npos) {
                word = words.substr(0, i);
                result = result + spell_check(word) + " ";
                words = words.substr(i+1);
            } else {
                word = words;
                result = result + spell_check(word);
            }
        }
    }
    file.close();
    cout << result << endl;
    unload();
    system("pause");
    return 0;
}
