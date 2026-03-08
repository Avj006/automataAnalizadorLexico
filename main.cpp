#include <iostream>
#include <string>
#include "State.h"
#include "Automaton.h"

using namespace std;

int main() {
    // Creamos los estados con su respectivo tipo
    State q0("q0", false, false, "inicio");
    State q1("q1", true, false, "integer");
    State q2("q2", false, false, "integer");   // punto decimal: sigue siendo parte de un numero
    State q3("q3", true, false, "float");
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

string word = "tmp = 32.4 *(-8.6 - b)/ 6.1";

cout << boolalpha << automaton.accept(word) << endl;

// ---- IMPRESIÓN DINÁMICA DE LA TABLA DE TOKENS ----
automaton.printTokens(word);

return 0;
}