import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

/**
 * Created by noureldin on 2/20/17.
 */
//ioi0523
public class main {
    private static int [] [] H = new int[102][102];
    private static int [] [] U = new int[120][102];
    private static int [] [] D = new int[102][102];
    private static int [] [] L = new int[120][102];
    private static int [] [] R = new int[102][102];
    private static int [] [] LU = new int[120][102];
    private static int [] [] LD = new int[102][102];
    private static int [] [] RU = new int[120][102];
    private static int [] [] RD = new int[102][102];

    private static int m,n;

    private static void pad(){
        for (int col = 0;col <= n + 1;col++) H[0][col] = H[m + 1][col] = 0;
        for (int row = 0;row <= m + 1;row++) H[row][0] = H[row][n + 1] = 0;
        for (int row = 0;row <= m + 1;row++)
            for (int col = 0;col <= n + 1;col++) {
                U[row][col] = D[row][col] = L[row][col] = R[row][col] = 0;
                RU[row][col] = RD[row][col] = LU[row][col] = LD[row][col] = 0;
            }
    }
    private static void preprocess(){
        pad();
        for (int row = 1;row <= m;row++)
            for (int col = 1;col <= n;col++){
                U[row][col] = Math.max(U[row - 1][col],H[row - 1][col]);
                L[row][col] = Math.max(L[row][col - 1],H[row][col - 1]);
            }
        for (int row = m;row >= 1;row--)
            for (int col = n;col >= 1;col--){
                D[row][col] = Math.max(D[row + 1][col],H[row + 1][col]);
                R[row][col] = Math.max(R[row][col + 1],H[row][col + 1]);
            }
    }

    private static int solve() {
        int ret = 0;
        for (int row = 1; row <= m; row++)
            for (int col = 1; col <= n; col++)
                LU[row][col] = Math.max(H[row][col],Math.min(LU[row - 1][col], LU[row][col - 1]));
        for (int row = m; row >= 1; row--)
            for (int col = 1; col <= n; col++)
                LD[row][col] = Math.max(H[row][col],Math.min(LD[row + 1][col],LD[row][col - 1]));
        for (int row = 1; row <= m; row++)
            for (int col = n; col >= 1; col--)
                RU[row][col] = Math.max(H[row][col],Math.min(RU[row - 1][col],RU[row][col + 1]));
        for (int row = m; row >= 1; row--)
            for (int col = n; col >= 1; col--)
                RD[row][col] = Math.max(H[row][col],Math.min(RD[row + 1][col],RD[row][col + 1]));
        for (int row = 1; row <= m; row++)
            for (int col = 1; col <= n; col++) {
                int h = Math.min(LU[row][col],RU[row][col]);
                h = Math.min(h,LD[row][col]);
                h = Math.min(h,RD[row][col]);
                ret += h - H[row][col];
            }
        return ret;
    }
    /*
                    int h = Math.min(LU[row - 1][col], LU[row][col - 1]);
                if (h == H[row - 1][col] || h == H[row][col - 1])
                    h = Math.min(h,LU[row - 1][col - 1]);
                LU[row][col] = Math.max(h,H[row][col]);

     */
    public static void main(String[] args) throws Exception{
        IO io = new IO(null,null);
        int T = io.getNextInt();
        for(int t = 1;t <= T;t++){
            m = io.getNextInt();
            n = io.getNextInt();
            for (int i = 1;i <= m;i++)
                for (int j = 1;j <= n;j++)
                    H[i][j] = io.getNextInt();
            preprocess();
            io.println(solve());
        }
        io.close();
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


