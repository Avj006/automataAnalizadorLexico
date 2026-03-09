#ifndef STATE_H
#define STATE_H

#include <string>
#include <unordered_map>
using namespace std;

class State {
    public:
        string name; //ej. q0, q1, etc...
        bool isFinal; //¿es final?
        bool isDeathState; //¿es estado muerto?
        string type; // Atributo para guardar el tipo de token leido

        //hash table para transiciones de cada nodo
        unordered_map<string, State*> transitions;
        
        //hash table para los operadores y los parentesis: accede segun el key (token detectado)
        unordered_map<string, string> HashTableSymbolIdentifier{ //ESTADO q4 y q5
            {"=", "assignment"},
            {"*", "product"},
            {"-", "subtract"},
            {"/", "division"},
            {"+", "sum"},
            {")", "right parenthesis"},
            {"(", "left parenthesis"}
        };

        //Constructor
        State(string name, bool isFinal, bool isDeathState, string type) {
            this->name = name;
            this->isFinal = isFinal;
            this->isDeathState = isDeathState;
            this->type = type; 
        }

        //Inicializar la hash table de cada estado con sus respectivas relaciones con otros estadoss
        void addTransition(string symbol, State* state) {
            this->transitions[symbol] = state; 
        }

        // transicion al siguiente estado :)
        State* getNextState(string symbol) {
            if (this->transitions.find(symbol) != this->transitions.end()) {
                return this->transitions[symbol]; //este es el que recorre con apoyyo de las transiciones que hicimos (hash table)
            }
            return nullptr; 
        }

        /* Codigo hecho en clase
        string toString() {
            return "name: " + this->name + 
                ", isFinal: " + (this->isFinal ? "true" : "false") + 
                ", isDeathState: " + (this->isDeathState ? "true" : "false") +
                ", type: " + this->type;
        }*/
        
        void hashTableAux(const string tipoInput[], int size, State* proxEstado) { // funcion para agregar transiciones a la hash table de cada estado con los respectivos carácteres válidos 
        for (int i = 0; i < size; i++) {
                this->addTransition(tipoInput[i], proxEstado);  //usa los arreglos declarados en el main
            }
        }
};

#endif