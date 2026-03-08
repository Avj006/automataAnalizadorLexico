#ifndef STATE_H
#define STATE_H

#include <string>
#include <unordered_map>
using namespace std;

class State {
public:
    string name;
    bool isFinal;
    bool isDeathState;
    string type; // Atributo para guardar el tipo de token
    //HASH TABLES
    unordered_map<string, State*> transitions;


    // Se agrega 'type' como cuarto parámetro en el constructor
    State(string name, bool isFinal, bool isDeathState, string type) {
        this->name = name;
        this->isFinal = isFinal;
        this->isDeathState = isDeathState;
        this->type = type; 
    }

    void addTransition(string symbol, State* state) {
        this->transitions[symbol] = state; 
    }

    State* getNextState(string symbol) {
        if (this->transitions.find(symbol) != this->transitions.end()) {
            return this->transitions[symbol];
        }
        return nullptr; 
    }

    string toString() {
        return "name: " + this->name + 
               ", isFinal: " + (this->isFinal ? "true" : "false") + 
               ", isDeathState: " + (this->isDeathState ? "true" : "false") +
               ", type: " + this->type;
    }

    void hashTableAux(const string tipoInput[], int size, State* proxEstado) {
        for (int i = 0; i < size; i++) {
            this->addTransition(tipoInput[i], proxEstado);  
        }
    }

    //hash table para los operadores y los parentesis
    unordered_map<string, string> HashTableSymbolIdentifier{ //ESTADO q4 y q5
        {"=", "assignment"},
        {"*", "product"},
        {"-", "subtract"},
        {"/", "division"},
        {"+", "addition"},
        {")", "right parenthesis"},
        {"(", "left parenthesis"}
    };

};

#endif