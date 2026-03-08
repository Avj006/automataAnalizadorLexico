#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>
#include <iostream>
#include "State.h"

using namespace std;

class Automaton {
public:
State* s; 

Automaton(State* s) {
this->s = s;
}

// ---- Metodo interno que ejecuta el recorrido del automata ----
bool runAutomaton(string word, bool printTokens){

bool result = false;

if (word.length() == 0) {
if (s->isFinal) {
result = true;
}
} else {
//return false; 
}

State* currentState = s;

string current_token = "";

if(printTokens){
cout << "\nTabla de Tokens:" << endl;
cout << "TOKEN\t\tTIPO" << endl;
cout << "----------------------------------" << endl;
}

for (size_t i = 0; i < word.length(); i++) {

string symbol = word.substr(i, 1); // Extrae el caracter actual
State* nextState = currentState->getNextState(symbol);

if (nextState == nullptr) {

if(printTokens){
if (!current_token.empty() && currentState->type != "inicio") {
cout << current_token << "\t\t" << currentState->type << endl;
}
}

return false;
}

if (nextState->isDeathState) {

if(printTokens){
if (!current_token.empty() && currentState->type != "inicio") {
cout << current_token << "\t\t" << currentState->type << endl;
}
}

return false;
}

if(printTokens){

if (currentState->type != nextState->type) {

if (!current_token.empty() && currentState->type != "inicio") {
cout << current_token << "\t\t" << currentState->type << endl;
}

current_token = "";
}

if (symbol != " ") {
current_token += symbol;
}

}

if(nextState->isFinal){
result = true;
} else {
result = false;
}

currentState = nextState;
}

if(printTokens){
if (!current_token.empty() && currentState->type != "inicio") {
cout << current_token << "\t\t" << currentState->type << endl;
}
}

return result;

}

bool accept(string word) {
return runAutomaton(word,false);
}

void printTokens(string word){
runAutomaton(word,true);
}

};

#endif