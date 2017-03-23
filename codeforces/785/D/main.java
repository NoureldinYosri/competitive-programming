import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

/**
 * Created by noureldin on 2/20/17.
 */

public class main {

    private static int mod = 1000*100*1000 + 7,MAX = 200*1000 + 10;
    private static int [] F = new int[MAX];
    private static int [] r = new int[MAX];

    private static int mul(int x,int y){
        return (int)((x*1L*y)%mod);
    }
    private static int add(int x,int y){
        x += y;
        if(x >= mod) x -= mod;
        return x;
    }

    private static int C(int n,int k){
        if (n < k) return 0;
        return mul(mul(F[n],r[k]),r[n - k]);
    }
    private static int pow_mod(int x,int p){
        if(p == 0) return 1;
        int y = 1;
        for(;p > 1;p >>= 1){
            if(p%2 == 1) y = mul(x,y);
            x = mul(x,x);
        }
        return mul(x,y);
    }
    private static void init(){
        F[0] = r[0] = 1;
        for (int i = 0;i < MAX - 1;i++){
            F[i + 1] = mul(F[i],i + 1);
            r[i + 1] = pow_mod(F[i + 1],mod - 2);
        }
    }

    public static void main(String[] args) throws Exception{
        IO io = new IO(null,null);
        init();
        char [] I = io.getNext().toCharArray();
        int open = 0;
        for (char c : I) open += (c == '(') ? 1 : 0;
        int ans = 0,cnt = 0;
        for (int i = 0;i < I.length;i++){
            if (I[i] == ')') continue;
            cnt ++;
            int m = I.length - open - i - 1 + cnt;
//            System.out.println(cnt + " " + m + " " + C(m + cnt - 2,m - 1));
            ans = add(ans,C(m + cnt - 1,cnt ));
        }
        io.println(ans);
        io.close();
    }
}

class event implements Comparable<event>{
    int t,type;
    public event(int t,int type){
        this.t = t;
        this.type = type;
    }
    @Override
    public int compareTo(event o){
        if (this.t != o.t) return this.t - o.t;
        return this.type - o.type;
    }
}


class IO{
    private BufferedReader br;
    private StringTokenizer st;
    private PrintWriter writer;
    private String inputFile,outputFile;

    public String getNext() throws FileNotFoundException, IOException{
        while(st == null || !st.hasMoreTokens()) st = new StringTokenizer(br.readLine());
        return st.nextToken();
    }

    public String getNextLine() throws FileNotFoundException, IOException{
        return br.readLine();
    }

    public int getNextInt() throws FileNotFoundException, IOException{
        return Integer.parseInt(getNext());
    }
    public long getNextLong() throws FileNotFoundException, IOException{
        return Long.parseLong(getNext());
    }

    public void print(double x,int num_digits) throws  IOException{
        writer.printf("%." + num_digits + "f" ,x);
    }
    public void println(double x,int num_digits) throws  IOException{
        writer.printf("%." + num_digits + "f\n" ,x);
    }
    public void print(Object o) throws  IOException{
        writer.print(o.toString());
    }

    public void println(Object o) throws  IOException{
        writer.println(o.toString());
    }
    public IO(String x,String y) throws FileNotFoundException, IOException{
        inputFile = x;
        outputFile = y;
        if(x != null) br = new BufferedReader(new FileReader(inputFile));
        else br = new BufferedReader(new InputStreamReader(System.in));
        if(y != null) writer = new PrintWriter(new BufferedWriter(new FileWriter(outputFile)));
        else writer = new PrintWriter(new OutputStreamWriter(System.out));
    }

    protected void close() throws IOException{
        br.close();
        writer.close();
    }
}


