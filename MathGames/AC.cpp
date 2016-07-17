import java.util.*;


public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        while(in.hasNext()) {
            int n = in.nextInt();
            String winner = "Bob";
            // Bob almost always wins using a mirroring strategy
            if(n == 0 ) {
                break;
            } else if(n <= 2) {
                winner = "Alice";
            }
            System.out.println(winner);
        }
    }
}

