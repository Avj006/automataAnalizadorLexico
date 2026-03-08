#include <iostream>
#include <string>
#include "State.h"
#include "Automaton.h"

using namespace std;

int main() {
    // Creamos los estados (los almacenamos en la memoria local)
    State q0("q0", false, false);
    State q1("q1", true, false);
    State q2("q2", false, false);
    State q3("q3", true, false);
    State q4("q4", true, false);
    State q5("q5", true, false);
    State q6("q6", true, false);
    State theta("theta", false, true);

    // Definimos nuestras clases de caracteres para facilitar las transiciones
    string digits[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    string letters[26] = {"a", "b", "c", "d", "e", "f", "g", "h" "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    string operators[5] = {"+", "-", "=", "*", "/"};
    string parenthesis[2] = {"(", ")"};
    string space[1] = {" "};
    string point[1] = {"."};
    // Añadimos las transiciones pasando la dirección de memoria (&) de los estados

    //transiciones q0
    q0.auxiliarTablaHash(space, 1, &q0);            // espacio → q0
    q0.auxiliarTablaHash(digits, 10, &q1);          // 0-9 → q1
    q0.auxiliarTablaHash(letters, 26, &q6);        // a-z → q6  
    q0.auxiliarTablaHash(point, 1, &theta);        // . → theta
    q0.auxiliarTablaHash(operators, 5, &q4);       // +,-,etc → q4
    q0.auxiliarTablaHash(parenthesis, 2, &q5);     // () → q5
    
    //transiciones q1
    q1.auxiliarTablaHash(space, 1, &q1);            // espacio → q1
    q1.auxiliarTablaHash(digits, 10, &q1);          // 0-9 → q1
    q1.auxiliarTablaHash(letters, 26, &theta);      // a-z → theta  
    q1.auxiliarTablaHash(point, 1, &q2);           // . → q2
    q1.auxiliarTablaHash(operators, 5, &q4);       // +,-,etc → q4
    q1.auxiliarTablaHash(parenthesis, 2, &q5);     // () → q5
    
    //transiciones q2
    q2.auxiliarTablaHash(space, 1, &theta);            // espacio → theta
    q2.auxiliarTablaHash(digits, 10, &q3);          // 0-9 → q3
    q2.auxiliarTablaHash(letters, 26, &theta);        // a-z → theta  
    q2.auxiliarTablaHash(point, 1, &theta);        // . → theta
    q2.auxiliarTablaHash(operators, 5, &theta);       // +,-,etc → theta
    q2.auxiliarTablaHash(parenthesis, 2, &theta);     // () → theta
    
    //transiciones q3
    q3.auxiliarTablaHash(space, 1, &q3);            // espacio → q3
    q3.auxiliarTablaHash(digits, 10, &q3);          // 0-9 → q3
    q3.auxiliarTablaHash(letters, 26, &theta);        // a-z → theta 
    q3.auxiliarTablaHash(point, 1, &theta);        // . → theta
    q3.auxiliarTablaHash(operators, 5, &q4);       // +,-,etc → q4
    q3.auxiliarTablaHash(parenthesis, 2, &q5);     // () → q5

    //transiciones q4
    q4.auxiliarTablaHash(space, 1, &q4);            // espacio → q4
    q4.auxiliarTablaHash(digits, 10, &q1);          // 0-9 → q1
    q4.auxiliarTablaHash(letters, 26, &theta);      // a-z → theta  
    q4.auxiliarTablaHash(point, 1, &theta);        // . → theta
    q4.auxiliarTablaHash(operators, 5, &q4);       // +,-,etc → q4
    q4.auxiliarTablaHash(parenthesis, 2, &q5);     // () → q5

    //transiciones q5
    q5.auxiliarTablaHash(space, 1, &q5);           // espacio → q5
    q5.auxiliarTablaHash(digits, 10, &q1);         // 0-9 → q1
    q5.auxiliarTablaHash(letters, 26, &q6);        // a-z → q6  
    q5.auxiliarTablaHash(point, 1, &theta);        // . → theta
    q5.auxiliarTablaHash(operators, 5, &q4);       // +,-,etc → q4
    q5.auxiliarTablaHash(parenthesis, 2, &q5);     // () → q5

    //transiciones q6
    q6.auxiliarTablaHash(space, 1, &q6);            // espacio → q6
    q6.auxiliarTablaHash(digits, 10, &theta);       // 0-9 → theta
    q6.auxiliarTablaHash(letters, 26, &q6);         // a-z → q6  
    q6.auxiliarTablaHash(point, 1, &theta);        // . → theta
    q6.auxiliarTablaHash(operators, 5, &q4);       // +,-,etc → q4
    q6.auxiliarTablaHash(parenthesis, 2, &q5);     // () → q5

    //transiciones theta
    theta.auxiliarTablaHash(space, 1, &theta);          // espacio → theta
    theta.auxiliarTablaHash(digits, 10, &theta);       // 0-9 → theta
    theta.auxiliarTablaHash(letters, 26, &theta);       // a-z → theta 
    theta.auxiliarTablaHash(point, 1, &theta);          // . → theta
    theta.auxiliarTablaHash(operators, 5, &theta);       // +,-,etc → theta
    theta.auxiliarTablaHash(parenthesis, 2, &theta);     // () → theta
    
    
    // Creamos el autómata con un puntero al estado inicial "s"
    //Automaton automaton(&s);

    //string word = ""; // la cadena
    
    // std::boolalpha hace que se imprima "true" o "false" en lugar de 1 o 0
    //cout << boolalpha << automaton.accept(word) << endl;

    return 0;
}