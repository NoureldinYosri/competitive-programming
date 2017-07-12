
/*
A fast O(S*K*log(N) + N*log(N)) and correct solution to jewel thief.
*/

import java.util.*;
import java.io.*;

public class thief_font
{
   public static void main(String[] args) throws Exception
   {
      PrintWriter out = new PrintWriter(System.out);
      new thief_font(new FastScanner(System.in), out);
      out.close();
   }

   final static int MAX_S = 300;
   public thief_font(FastScanner in, PrintWriter out)
   {
      int N = in.nextInt();
      int K = in.nextInt();
      
      ArrayList<Integer>[] jewels = new ArrayList[MAX_S+1];
      for (int x=0; x<jewels.length; x++)
         jewels[x] = new ArrayList<Integer>();
      
      for (int i=0; i<N; i++)
      {
         int s = in.nextInt();
         int v = in.nextInt();
         jewels[s].add(v);
      }
      for (int x=0; x<jewels.length; x++)
         Collections.sort(jewels[x], Collections.reverseOrder());

      long[] dp = new long[K+1];
      Curve[] dq = new Curve[K+1];
      for (int s=0; s<jewels.length; s++) if (jewels[s].size() > 0)
      {
         int L = jewels[s].size();
         long[] sum = new long[L];
         for (int i=0; i<L; i++)
            sum[i] = jewels[s].get(i);

         for (int i=0; i+1<L; i++)
            sum[i+1] += sum[i];
         Curve.sum = sum;
         
         // Update each congruence class
         // Runtime O(K log N)
         for (int m=0; m<s; m++)
         {
            int start=K-m, j=1, fptr = 0, bptr = 0;
            for (int i=0; start-i*s>=0; i++)
            {
               // Relax outdated
               while (bptr-fptr > 0 && dq[fptr].a <= i)
                  fptr++;
               
               while (j-i <= L && (start-j*s) >= 0)
               {
                  int pos = start-j*s;
                  Curve nc = new Curve(j, i, dp[pos]);
                 
                  if (fptr < bptr)
                     dq[bptr-1].t = nc.ot(dq[bptr-1]);

                  // Maintain deque invariant
                  while (bptr-fptr > 1 && dq[bptr-1].t <= dq[bptr-2].t)
                  {
                     bptr--;
                     dq[bptr-1].t = nc.ot(dq[bptr-1]);
                  }

                  dq[bptr++] = nc;
                  j++;
               }


               // Relax overtaken
               while (bptr-fptr > 1 && dq[fptr].f(i) <= dq[fptr+1].f(i))
                  fptr++;

               // Update solution
               if (fptr < bptr)
               {
                  int pos = start-i*s;
                  dp[pos] = Math.max(dp[pos], dq[fptr].f(i));
               }
            }
         }
      }
   
      out.printf("%d", dp[1]);
      for (int x=2; x<=K; x++)
         out.printf(" %d", dp[x]);
      out.println();
   }
}

class Curve
{
   static long[] sum;
   int a, b, t;
   long c;

   Curve(int aa, int bb, long cc)
   {
      a=aa; b=bb; c=cc; 
   }

   long f(int x)
   {
      return x >= a ? 0 : (sum[a-x-1] + c);
   }

   // Calculate the earliest time this overtakes rhs
   int ot(Curve rhs)
   {
      int lo = b, hi = a-1;
      while (lo < hi)
      {
         int m = (lo+hi) / 2;
         if (f(m) >= rhs.f(m))
            hi = m;
         else
            lo = m+1;
      }
      return hi;
   }
}

class FastScanner{
    private InputStream stream;
    private byte[] buf = new byte[1024];
    private int curChar;
    private int numChars;
    
    public FastScanner(InputStream stream)
    {
        this.stream = stream;
    }
    
    int read()
    {
        if (numChars == -1)
            throw new InputMismatchException();
        if (curChar >= numChars){
            curChar = 0;
            try{
                numChars = stream.read(buf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (numChars <= 0)
                return -1;
        }
        return buf[curChar++];
    }
    
    boolean isSpaceChar(int c)
    {
        return c==' '||c=='\n'||c=='\r'||c=='\t'||c==-1;
    }
    
    boolean isEndline(int c)
    {
        return c=='\n'||c=='\r'||c==-1;
    }
    
    int nextInt()
    {
        return Integer.parseInt(next());
    }
    
    long nextLong()
    {
        return Long.parseLong(next());
    }
    
    double nextDouble()
    {
        return Double.parseDouble(next());
    }
    
    String next(){
        int c = read();
        while (isSpaceChar(c))
            c = read();
        StringBuilder res = new StringBuilder();
        do{
            res.appendCodePoint(c);
            c = read();
        }while(!isSpaceChar(c));
        return res.toString();
    }
    
    String nextLine(){
        int c = read();
        while (isEndline(c))
            c = read();
        StringBuilder res = new StringBuilder();
        do{
            res.appendCodePoint(c);
            c = read();
        }while(!isEndline(c));
        return res.toString();
    }
}
