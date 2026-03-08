#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>
#include "State.h"

class Automaton {
public:
    State* s; 

    Automaton(State* s) {
        this->s = s;
    }

    bool accept(string word) {
        bool result = false;
        
        if (word.length() == 0) {
            if (s->isFinal) { 
                result = true; 
            }
        }

        State* currentState = s; 
        
        for (size_t i = 0; i < word.length(); i++) {
            string symbol = word.substr(i, 1); 
            State* nextState = currentState->getNextState(symbol); 
            
            if (nextState == nullptr) { 
                return false;
            }
            if (nextState->isDeathState) { 
                return false;
            }

            if(nextState->isFinal){
                result = true; 
            } else {
                result = false; 
            }

            currentState = nextState; 
        }
        return result;
    }
};

#endif