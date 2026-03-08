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
    string type;
    unordered_map<string, State*> transitions;

    // Secondary map: symbol → specific token type label
    // Used by states like q4/q5 to distinguish =, +, -, *, /, (, )
    unordered_map<string, string> symbolTypes;

    State(string name, bool isFinal, bool isDeathState, string type) {
        this->name        = name;
        this->isFinal     = isFinal;
        this->isDeathState = isDeathState;
        this->type        = type;
    }

    void addTransition(string symbol, State* state) {
        this->transitions[symbol] = state;
    }

    // Register a specific label for a symbol within this state
    void addSymbolType(string symbol, string label) {
        this->symbolTypes[symbol] = label;
    }

    // Returns the specific type for a symbol if registered, otherwise the state's generic type
    string getTokenType(string symbol) {
        if (this->symbolTypes.find(symbol) != this->symbolTypes.end()) {
            return this->symbolTypes[symbol];
        }
        return this->type;
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

    void auxiliarTablaHash(const string tipoInput[], int size, State* proxEstado) {
        for (int i = 0; i < size; i++) {
            this->addTransition(tipoInput[i], proxEstado);
        }
    }
};

#endif
