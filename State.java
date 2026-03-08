package automaton602;

import java.util.HashMap;

public class State {
    String name;
    boolean isFinal;
    boolean isDeathState;
    HashMap<String, State> transitions;

    public State(String name, boolean isFinal, boolean isDeathState) {
        this.name = name;
        this.isFinal = isFinal;
        this.isDeathState = isDeathState;
        this.transitions = new HashMap<>();
    }

    public void addTransition(String symbol, State state) {
        this.transitions.put(symbol, state); // Add a transition for the given symbol to the specified state
    }

    public State getNextState(String symbol) {
        return this.transitions.get(symbol); // Retrieve the next state based on the input symbol
    }

    @Override
    public String toString() {
        return "name: " + this.name + ", isFinal: " + this.isFinal + ", isDeathState: " + this.isDeathState; 
        // Return a string representation of the state, including its name, whether it's a final state, and whether it's a death state
    }
}