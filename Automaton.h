#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>
#include <iostream>
#include "State.h"

using namespace std;

class Automaton {
    public:
        State* s;
        
        //Constructor
        Automaton(State* s) {
            this->s = s;
        }

        // Aqui activamos el automata (inicia el recorrido)
            //parametros: recide el input (palabra del txt) y una variable que elige si lo imprime o no
        void runAutomaton(string word, bool printTokens){
            /*
            bool result = false;
            if (word.length() == 0) {
                if (s->isFinal) {
                result = true;
                }
            } else {
                //return false; 
            }
            */
            
            if(printTokens){ // Si se desea imprimir los tokens, aqui esta la tabla
                cout << "\n---------- Output Table ----------"<< endl;
                cout << "Token\t\tType" << endl; //usamos tabuladores
                cout << "----------------------------------" << endl; //las lineas es para hacerlo mas legible
            }

            State* currentState = s;
            string current_token = "";
            string current_token_type = "";

            for (size_t i = 0; i < word.length(); i++) { //basado en el codigo hecho en clase, checa char por char la palabra
                string symbol = word.substr(i, 1); // Extrae el caracter actual
                State* nextState = currentState->getNextState(symbol); //busca la transicion de acuerdo con lo recibido

                if (nextState == nullptr) { //en caso de detectar algo no valido (algo no estipulado ni en los arreglos del main)
                    if(printTokens){ //si se quiere imprimir,
                        if (!current_token.empty()) { //y no esta vacio,
                            cout << current_token << "\t\t" << current_token_type << endl; //se muestra en la tabla
                        }
                    }
                    current_token = ""; //limpia el token porque en la actividad dice "will print a table with every recognized token" y, si cae en este caso, es porque se detecto un caso invalido; pero no por eso terminara de leer el resto de la linea del archivo .txt
                    continue; //continua por lo mismo, por esto no es un return ni un break
                }

                if (nextState->isDeathState) { //en caso de caer en theta (estado muerto)
                    if(printTokens){
                        if (!current_token.empty()) {
                        cout << current_token << "\t\t" << current_token_type << endl; //en caso de imprimir; por ejemplo Rod8lfo -> od lfo (R cae en el caso 1, linea 46 y el "8" depues de las letras cae en caso 2, linea 56 porque una variable no puede tenerlo)
                        }
                    }
                    current_token = ""; //limpia igual que en caso 1
                    continue;
                }

                if(printTokens){
                    string nextType = nextState->type; //identifica el tipo del token

                    bool isNumericTransition = (current_token_type == "integer" && nextType == "float") || (current_token_type == "float" && nextType == "float"); //aqui checa si se pasa de q0 -> q1 -> q2 (por lo que detecta esto como flotante, pero si se queda en q1 es integer). Tambien se prevee el caso donde sigue recibiendo mas cifras despues del punto decimal.

                    if (!current_token_type.empty() && nextType != current_token_type && !isNumericTransition) { //en caso de que no se tenga que verificar que sea una transicion de tipo numerica, no lo hace.
                        cout << current_token << "\t\t" << current_token_type << endl;
                        current_token = ""; //una vez impreso, se limpia para evitar fallas (token y tipo)
                        current_token_type = "";
                    }

                    if (symbol != " ") {
                        current_token += symbol; //concatenacion de strings (char por char)

                        if (current_token_type.empty()) {
                            current_token_type = nextType;
                        }

                        if (current_token_type == "integer" && nextType == "float") {
                            current_token_type = "float"; //aqui es cuando pone float al que llega a q2
                        }

                        if(current_token_type=="operator" || current_token_type=="parenthesis"){
                            current_token_type = nextState->HashTableSymbolIdentifier[current_token]; 
                            //sin embargo aqui, al detectar un tipo de operador o parentesis, accede a la tabla hash llamda "HashTableSymbolIdentifier" para acceder por la key (token) a su etiqueta respectiva.
                        }
                    }
                }

                /*
                if(nextState->isFinal){
                    result = true; 
                } else {
                    result = false;
                }
                */
                
                currentState = nextState; //recorre
            }

            if(printTokens){
                if (!current_token.empty()) {
                    cout << current_token << "\t\t" << current_token_type << endl; //imprime los tokens
                }
            }
            //return result;
        }

        void printTokens(string word){
            runAutomaton(word,true); //llama a runAutomaton (para poder llamarlo en main) para imprimir la tabla
        }

};

#endif