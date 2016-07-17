import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
import java.util.ArrayList;

/**
 *
 * @author noureldin
 */

class pollard_rho {
    private static BigInteger zero = new BigInteger("0");
    private static BigInteger one  = new BigInteger("1");
    private static BigInteger two  = new BigInteger("2");
    private static SecureRandom r = new SecureRandom();
    
    public static BigInteger factor(BigInteger N) {
        if (N.compareTo(one) == 0) return one;
        if (N.isProbablePrime(20)) return N;
        BigInteger d = rho(N);
        BigInteger ans = factor(d);
        if(ans.compareTo(one) != 0 && ans.compareTo(N) != 0) return ans;
        return factor(N.divide(d));
    }
 
    public static BigInteger rho(BigInteger N) {
        BigInteger d;
        BigInteger c  = new BigInteger(N.bitLength(), r);
        BigInteger p  = new BigInteger(N.bitLength(), r);
        BigInteger q = p;
 
        if (N.mod(two).compareTo(zero) == 0) return two;
 
        d = one;
        while(d.compareTo(one) == 0) {
            p  =  p.multiply(p).mod(N).add(c).mod(N);
            q = q.multiply(q).mod(N).add(c).mod(N);
            q = q.multiply(q).mod(N).add(c).mod(N);
            d = p.subtract(q).gcd(N);
        }
        return d;
    }
 
 
}

public class C {

    private static Boolean cond(String s){
        int L = s.length();
        for(int base = 2;base <= 10;base++){
            long m = 0;
            for(int i = 0;i < L;i++){
                m = m * base + (int)s.charAt(i) - (int)'0';
            }
            if(BigInteger.valueOf(m).isProbablePrime(30)) return false;
        }
        return true;
    }
    public static void main(String[] args) throws IOException {
        Queue<Long> cand = new LinkedList<Long>();
        ArrayList<LinkedList<Long>> sol = new ArrayList<LinkedList<Long> >();
        for(int i = 0;i < 17;i++) sol.add(new LinkedList<Long>());
        cand.add(1L);
        while(!cand.isEmpty()){
            long n = cand.poll();
            if(n >= 10000000000000000L) break;
            if((n & 1) > 0 && n != 1){
                String s = Long.toString(n);
                if(cond(s)){
                    int L = s.length();
                    sol.get(L).add(n);
                    if(L == 3) System.out.println(n);
                }
            }
            cand.add(n*10);
            cand.add(n*10 + 1);
        }
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int T = Integer.parseInt(br.readLine().trim());
        for(int t = 1;t <= T;t++){
            st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken()),J = Integer.parseInt(st.nextToken());
            System.out.printf("Case #%d:\n",t);
            for(int i = 0;i < J;i++){
                long n = sol.get(N).get(i);
                System.out.print(n);
                String s = Long.toString(n);
                for(int base = 2;base <= 10;base++){
                    long m = 0;
                    for(int j = 0;j < s.length();j++)
                        m = m * base + (int)s.charAt(j) - (int)'0';
                    System.out.print(" " + pollard_rho.factor(BigInteger.valueOf(m)));
                }
                System.out.println();
            }
        }
    }
    
}

