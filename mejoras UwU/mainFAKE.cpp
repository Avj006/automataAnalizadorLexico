#include <iostream>
#include <string>
#include "State.h"
#include "Automaton.h"

using namespace std;

int main() {
    // Creamos los estados con su respectivo tipo
    State q0("q0", false, false, "inicio");
    State q1("q1", true, false, "numero");
    State q2("q2", false, false, "numero");   // punto decimal: sigue siendo parte de un numero
    State q3("q3", true, false, "decimal");
    State q4("q4", true, false, "operador");
    State q5("q5", true, false, "parentesis");
    State q6("q6", true, false, "variable");
    State theta("theta", false, true, "Dead state");

    // Clases de caracteres
    string digits[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    string letters[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    string operators[5] = {"+", "-", "=", "*", "/"};
    string parenthesis[2] = {"(", ")"};
    string space[1] = {" "};
    string point[1] = {"."};

    // transiciones q0
    q0.auxiliarTablaHash(space, 1, &q0);            
    q0.auxiliarTablaHash(digits, 10, &q1);          
    q0.auxiliarTablaHash(letters, 26, &q6);        
    q0.auxiliarTablaHash(point, 1, &theta);        
    q0.auxiliarTablaHash(operators, 5, &q4);       
    q0.auxiliarTablaHash(parenthesis, 2, &q5);     
    
    // transiciones q1
    q1.auxiliarTablaHash(space, 1, &q1);            
    q1.auxiliarTablaHash(digits, 10, &q1);          
    q1.auxiliarTablaHash(letters, 26, &theta);      
    q1.auxiliarTablaHash(point, 1, &q2);           
    q1.auxiliarTablaHash(operators, 5, &q4);       
    q1.auxiliarTablaHash(parenthesis, 2, &q5);     
    
    // transiciones q2
    q2.auxiliarTablaHash(space, 1, &theta);            
    q2.auxiliarTablaHash(digits, 10, &q3);          
    q2.auxiliarTablaHash(letters, 26, &theta);        
    q2.auxiliarTablaHash(point, 1, &theta);        
    q2.auxiliarTablaHash(operators, 5, &theta);       
    q2.auxiliarTablaHash(parenthesis, 2, &theta);     
    
    // transiciones q3
    q3.auxiliarTablaHash(space, 1, &q3);            
    q3.auxiliarTablaHash(digits, 10, &q3);          
    q3.auxiliarTablaHash(letters, 26, &theta);        
    q3.auxiliarTablaHash(point, 1, &theta);        
    q3.auxiliarTablaHash(operators, 5, &q4);       
    q3.auxiliarTablaHash(parenthesis, 2, &q5);     

    // transiciones q4
    q4.auxiliarTablaHash(space, 1, &q4);            
    q4.auxiliarTablaHash(digits, 10, &q1);          
    q4.auxiliarTablaHash(letters, 26, &q6);      
    q4.auxiliarTablaHash(point, 1, &theta);        
    q4.auxiliarTablaHash(operators, 5, &q4);       
    q4.auxiliarTablaHash(parenthesis, 2, &q5);     

    // transiciones q5
    q5.auxiliarTablaHash(space, 1, &q5);           
    q5.auxiliarTablaHash(digits, 10, &q1);         
    q5.auxiliarTablaHash(letters, 26, &q6);        
    q5.auxiliarTablaHash(point, 1, &theta);        
    q5.auxiliarTablaHash(operators, 5, &q4);       
    q5.auxiliarTablaHash(parenthesis, 2, &q5);     

    // transiciones q6
    q6.auxiliarTablaHash(space, 1, &q6);            
    q6.auxiliarTablaHash(digits, 10, &theta);       
    q6.auxiliarTablaHash(letters, 26, &q6);         
    q6.auxiliarTablaHash(point, 1, &theta);        
    q6.auxiliarTablaHash(operators, 5, &q4);       
    q6.auxiliarTablaHash(parenthesis, 2, &q5);     

    // transiciones theta
    theta.auxiliarTablaHash(space, 1, &theta);          
    theta.auxiliarTablaHash(digits, 10, &theta);       
    theta.auxiliarTablaHash(letters, 26, &theta);       
    theta.auxiliarTablaHash(point, 1, &theta);          
    theta.auxiliarTablaHash(operators, 5, &theta);       
    theta.auxiliarTablaHash(parenthesis, 2, &theta);     
    
    Automaton automaton(&q0);

    string word = "tmp = 32.4 *(-8.6 - b)/       6.1"; 
    
    cout << boolalpha << automaton.accept(word) << endl;

    // ---- IMPRESIÓN DINÁMICA DE LA TABLA DE TOKENS ----
    cout << "\nTabla de Tokens:" << endl;
    cout << "TOKEN\t\tTIPO" << endl;
    cout << "----------------------------------" << endl;

    string current_token = "";
    State* curr = &q0;
    // Guardamos el tipo del token que estamos armando actualmente.
    // Usamos el tipo del primer estado significativo que inicia el token.
    string current_token_type = "";

    for (size_t i = 0; i < word.length(); i++) {
        string symbol = word.substr(i, 1);
        State* nextState = curr->getNextState(symbol);

        if (nextState == nullptr || nextState->isDeathState) {
            if (!current_token.empty()) {
                cout << current_token << "\t\t" << current_token_type << endl;
            }
            current_token = "";
            current_token_type = "";
            curr = &q0; // reiniciar al estado inicial para continuar
            // No avanzamos i: re-procesamos el símbolo conflictivo desde q0
            // Pero como el flujo normal terminaría aquí, simplemente cortamos.
            break;
        }

        // Determinar si hay un cambio de token real.
        // "numero" y "decimal" son parte del mismo token numérico;
        // q2 también tiene tipo "numero" (lo cambiamos arriba), así que
        // el corte sólo ocurre cuando el tipo del PRÓXIMO estado es
        // categorialmente distinto al tipo que inició el token actual.
        string nextType = nextState->type;

        // Si el próximo tipo es diferente al tipo con el que empezó el token actual
        // Y no estamos en una transición interna dentro de un número (numero→decimal)
        bool isNumericTransition = (current_token_type == "numero" && nextType == "decimal")
                                || (current_token_type == "decimal" && nextType == "decimal");

        if (!current_token_type.empty() && nextType != current_token_type && !isNumericTransition) {
            // Emitir el token acumulado
            cout << current_token << "\t\t" << current_token_type << endl;
            current_token = "";
            current_token_type = "";
        }

        // Acumular símbolo (ignorar espacios en el valor del token)
        if (symbol != " ") {
            current_token += symbol;
            // Fijar el tipo del token si aún no está fijado
            if (current_token_type.empty()) {
                current_token_type = nextType;
            }
            // Si venimos de "numero" y entramos a "decimal", actualizamos el tipo final
            if (current_token_type == "numero" && nextType == "decimal") {
                current_token_type = "decimal";
            }
        } else {
            // Es un espacio: si el tipo cambia (p.ej. pasamos de q3 a q3 con espacio, ok)
            // pero si hay cambio de categoría en el siguiente no-espacio, ya lo veremos.
            // Solo actualizamos el tipo si aún no está fijado y el next es significativo.
        }

        curr = nextState;
    }

    // Imprimir el remanente si la cadena terminó en buen estado
    if (!current_token.empty()) {
        cout << current_token << "\t\t" << current_token_type << endl;
    }

    return 0;
}
