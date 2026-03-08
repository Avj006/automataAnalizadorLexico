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
string current_token_type = "";

if(printTokens){
cout << "\n ⬇️ Output table\n" << endl;
cout << "TOKEN\t\tTIPO" << endl;
cout << "----------------------------------" << endl;
}

for (size_t i = 0; i < word.length(); i++) {

string symbol = word.substr(i, 1); // Extrae el caracter actual
State* nextState = currentState->getNextState(symbol);

if (nextState == nullptr) {

if(printTokens){
if (!current_token.empty()) {
cout << current_token << "\t\t" << current_token_type << endl;
}
}

return false;
}

if (nextState->isDeathState) {

if(printTokens){
if (!current_token.empty()) {
cout << current_token << "\t\t" << current_token_type << endl;
}
}

return false;
}

if(printTokens){

string nextType = nextState->type;

bool isNumericTransition =
(current_token_type == "integer" && nextType == "float") ||
(current_token_type == "float" && nextType == "float");

if (!current_token_type.empty() && nextType != current_token_type && !isNumericTransition) {

cout << current_token << "\t\t" << current_token_type << endl;
current_token = "";
current_token_type = "";
}

if (symbol != " ") {

current_token += symbol;

if (current_token_type.empty()) {
current_token_type = nextType;
}

if (current_token_type == "integer" && nextType == "float") {
current_token_type = "float";
}

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
if (!current_token.empty()) {
cout << current_token << "\t\t" << current_token_type << endl;
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