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
    unordered_map<string, State*> transitions;


    State(string name, bool isFinal, bool isDeathState) {
        this->name = name;
        this->isFinal = isFinal;
        this->isDeathState = isDeathState;
    }

    void addTransition(string symbol, State* state) {
        // Añade la transición al mapa
        this->transitions[symbol] = state; 
    }

    State* getNextState(string symbol) {
        // En C++, buscamos si el símbolo existe para no crear entradas vacías
        if (this->transitions.find(symbol) != this->transitions.end()) {
            return this->transitions[symbol];
        }
        return nullptr; // Equivalente a null en Java
    }

    string toString() {
        return "name: " + this->name + 
               ", isFinal: " + (this->isFinal ? "true" : "false") + 
               ", isDeathState: " + (this->isDeathState ? "true" : "false");
    }

    // Agregar todas las transiciones de una categoría
    void auxiliarTablaHash(const string tipoInput[], int size, State* proxEstado) {
        for (int i = 0; i < size; i++) {
            this->addTransition(tipoInput[i], proxEstado);  
        }
    }
};

#endif