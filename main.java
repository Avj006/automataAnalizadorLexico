package automaton602;


public class Main {
    public static void main(String[] args) {

        State s = new State("s",false, false);
        State b = new State("b", false, false);
        State bb = new State("bb", true, false);

        s.addTransition("a", s);
        s.addTransition("b", b);
        b.addTransition("a", s);
        b.addTransition("b", bb);
        bb.addTransition("a", bb);
        bb.addTransition("b", bb);

        Automaton automaton = new Automaton(s);

        String word= ""; //la cadena
        System.out.println(automaton.accept(word)); //Muestra si la cadena es aceptada por el autómata o no


    }
}