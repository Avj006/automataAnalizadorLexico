package automaton602;


public class Automaton {
    State s;

    public Automaton(State s) {
        this.s = s;
    }

    public boolean accept(String word) {
        boolean result = false; // Initialize the result to false
        if (word.length() == 0) {
            if (s.isFinal) { // Si el estado s es un estado final, entonces aceptamos la cadena vacía
                result = true; 
            }
        } else {
            return false;

        }

        State currentState = s; // Start from the initial state
        for(int i=0; i<word.length(); i++) {
            String symbol = word.substring(i, i+1); // Get the current symbol from the word
            State nextState = currentState.getNextState(symbol); // Get the next state based on the current symbol
            
            if (nextState == null) { // If there is no transition for the current symbol, we reject the word
                return false;
            }
            if (nextState.isDeathState) { // If the next state is a death state, we reject the word
                return false;
            }

            if(nextState.isFinal){
                result = true; // necesitamos leer toda la cadena
            }
            else{
                result = false; // Si el siguiente estado no es un estado final, entonces no aceptamos la cadena
            }

            currentState = nextState; // Move to the next state
        }
        return result;
    }
}