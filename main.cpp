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
    State q4("q4", true, false, "operator");
    State q5("q5", true, false, "parenthesis");
    State q6("q6", true, false, "variable");
    State theta("theta", false, true, "Dead state");

    // Clases de caracteres
    string digits[10] = {"0","1","2","3","4","5","6","7","8","9"};
    string letters[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    string operators[5] = {"+","-","=","*","/"};
    string parenthesis[2] = {"(",")"};
    string space[1] = {" "};
    string point[1] = {"."};

    // transiciones q0
    q0.hashTableAux(space,1,&q0);
    q0.hashTableAux(digits,10,&q1);
    q0.hashTableAux(letters,26,&q6);
    q0.hashTableAux(point,1,&theta);
    q0.hashTableAux(operators,5,&q4);
    q0.hashTableAux(parenthesis,2,&q5);

    // transiciones q1
    q1.hashTableAux(space,1,&q1);
    q1.hashTableAux(digits,10,&q1);
    q1.hashTableAux(letters,26,&theta);
    q1.hashTableAux(point,1,&q2);
    q1.hashTableAux(operators,5,&q4);
    q1.hashTableAux(parenthesis,2,&q5);

    // transiciones q2
    q2.hashTableAux(space,1,&theta);
    q2.hashTableAux(digits,10,&q3);
    q2.hashTableAux(letters,26,&theta);
    q2.hashTableAux(point,1,&theta);
    q2.hashTableAux(operators,5,&theta);
    q2.hashTableAux(parenthesis,2,&theta);

    // transiciones q3
    q3.hashTableAux(space,1,&q3);
    q3.hashTableAux(digits,10,&q3);
    q3.hashTableAux(letters,26,&theta);
    q3.hashTableAux(point,1,&theta);
    q3.hashTableAux(operators,5,&q4);
    q3.hashTableAux(parenthesis,2,&q5);

    // transiciones q4
    q4.hashTableAux(space,1,&q4);
    q4.hashTableAux(digits,10,&q1);
    q4.hashTableAux(letters,26,&q6);
    q4.hashTableAux(point,1,&theta);
    q4.hashTableAux(operators,5,&q4);
    q4.hashTableAux(parenthesis,2,&q5);

    // transiciones q5
    q5.hashTableAux(space,1,&q5);
    q5.hashTableAux(digits,10,&q1);
    q5.hashTableAux(letters,26,&q6);
    q5.hashTableAux(point,1,&theta);
    q5.hashTableAux(operators,5,&q4);
    q5.hashTableAux(parenthesis,2,&q5);

    // transiciones q6
    q6.hashTableAux(space,1,&q6);
    q6.hashTableAux(digits,10,&theta);
    q6.hashTableAux(letters,26,&q6);
    q6.hashTableAux(point,1,&theta);
    q6.hashTableAux(operators,5,&q4);
    q6.hashTableAux(parenthesis,2,&q5);

    // transiciones theta
    theta.hashTableAux(space,1,&theta);
    theta.hashTableAux(digits,10,&theta);
    theta.hashTableAux(letters,26,&theta);
    theta.hashTableAux(point,1,&theta);
    theta.hashTableAux(operators,5,&theta);
    theta.hashTableAux(parenthesis,2,&theta);

    Automaton automaton(&q0);

    string word = "tmp = 32.44 */(-8.6 - b)/ 6.1";

    //cout << boolalpha << automaton.accept(word) << endl;

    // ---- TABLITA ----
    automaton.printTokens(word); //aquí debemos cambiarle lo de la hash para los operadores y parentesis
    cout<<endl;
    return 0;
}