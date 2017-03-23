import java.io.*;
import java.util.*;

/**
 * Created by noureldin on 2/20/17.
 */
public class main {
    private static final int MAXN = 201*1010 + 10,MAXLG = 20;
    private static IO io;
    private static ArrayList<Integer> [] G = new ArrayList[MAXN],W = new ArrayList[MAXN];
    private static int [] vis = new int[MAXN],to = new int[MAXN];
    private static boolean [] inCycle = new boolean[MAXN];
    private static int n,dfs_time;
    private static int [] treeDist = new int[MAXN],lg = new int[MAXN];
    private static int [] ord = new int [MAXN],lst = new int[MAXN],depth = new int[MAXN];
    private static int [] [] sparseTable = new int[MAXN][MAXLG];
    private static int [] first = new int[MAXN],second = new int[MAXN],cycleDist = new int[MAXN];

    private static void readGraph() throws Exception{
        HashMap<Integer,Integer> [] HM = new HashMap[n+1];
        for(int i = 0;i <= n;i++){
            G[i] = new ArrayList<Integer>();
            W[i] = new ArrayList<Integer>();
            HM[i] = new HashMap<Integer,Integer>();
        }
        for(int i = 0;i < n;i++){
            int a = io.getNextInt(),b = io.getNextInt(),c = io.getNextInt();
            if(a > b){ int t = a; a = b;b = t;}
            if(!HM[a].containsKey(b)) HM[a].put(b,1001);
            int val = HM[a].get(b);
            val = Math.min(val,c);
            HM[a].put(b,val);
        }
        for(int u = 0;u < n;u++)
            for(int v : HM[u].keySet()) {
                int w = HM[u].get(v);
                G[u].add(v); W[u].add(w);
                G[v].add(u); W[v].add(w);
            }
    }

    private static int dfsGetCycle(int u,int p) throws Exception{
        if(vis[u] != 0){
            if(vis[u] == 2) return -1;
            else return u;
        }
        vis[u] = 1;
        int ret = -1;
        for(int v : G[u]) if(v != p){
            int t = dfsGetCycle(v,u);
            if(t == -1) continue;
            inCycle[u] = true;
            if(ret != -1) throw new Exception("error in dfsGetCycle");
            ret = t;
        }
        if(ret == u) ret = -1;
        vis[u] = 2;
        return ret;
    }

    private static void getCycle() throws Exception{
        for(int i = 0;i <= n;i++) {
            vis[i] = 0;
            inCycle[i] = false;
        }
        dfsGetCycle(0,-1);
//        for(int i = 0;i < n;i++) if(inCycle[i]) System.out.print(i + " ");
//        System.out.println();
    }

    private static void compress() {
        for (int u = 0; u < n; u++) {
            if (inCycle[u]) {
                for (int i = 0, L = G[u].size(); i < L; i++) {
                    int v = G[u].get(i), w = W[u].get(i);
                    if (inCycle[v]) continue;
                    G[n].add(v);
                    W[n].add(w);
                }
            }
        }
    }
    private static void getOuter(){
        boolean isThereCycle = false;
        for(int i = 0;i <= n;i++) if(inCycle[i]){
            isThereCycle = true;
            Stack<Integer> Node = new Stack<Integer>(),
                    P = new Stack<Integer>();
            Node.add(i); P.add(-1);
            while(!Node.empty()){
                int u = Node.pop(),p = P.pop();
                to[u] = i;
                for(int v : G[u]) if(v != p && !inCycle[v]){
                    Node.add(v);
                    P.add(u);
                }
             //   System.out.println(u + " -> " + i);
            }
        }
        if(!isThereCycle){
            for(int i = 0;i <= n;i++) to[i] = -1;
        }
    }

    private static void dfsTree(int u,int p) throws Exception{
        lst[u] = dfs_time;
        ord[dfs_time++] = u;
        depth[u] = (p == -1) ? 0 : (depth[p] + 1);
        for(int i = 0,L = G[u].size();i < L;i++){
            int t = G[u].get(i),v = inCycle[t] ? n : t,w = W[u].get(i);
            if(v == p) continue;
            if(v == u) throw new Exception("error in dfsTree");
            treeDist[v] = treeDist[u] + w;
            dfsTree(v,u);
            lst[u] = dfs_time;
            ord[dfs_time++] = u;
        }
    }

    private static int argmin(int a,int b){
        if(depth[a] < depth[b]) return a;
        return b;
    }
    private static int lca(int a,int b){
        a = lst[a]; b = lst[b];
        if(a > b) {int t = a; a = b; b = t;}
        int l = lg[b - a + 1];
        return argmin(sparseTable[a][l],sparseTable[b - (1 << l) + 1][l]);
    }
    private static void buildRMQ(){
        lg[0] = -1;
        for(int i = 0;i < dfs_time;i++){
            int j = i + 1;
            lg[j] = lg[i] + (((j & (-j)) == j) ? 1 : 0);
        }
        for(int i = 0;i < dfs_time;i++) sparseTable[i][0] = ord[i];
        for(int k = 0;k < MAXLG - 1;k++)
            for(int i = 0;i < dfs_time;i++){
                int j = i + (1 << k);
                if(j >= dfs_time) j = i;
                sparseTable[i][k + 1] = argmin(sparseTable[i][k],sparseTable[j][k]);
            }
    }
    private static void buildTree() throws Exception{
        int root = -1;
        for(int i = 0;i < n;i++) if(!inCycle[i]) {
            root = i;
            break;
        }
        if(root == -1) return;
        for(int i = 0;i <= n;i++) treeDist[i] = 0;
        dfs_time = 0;
        dfsTree(root,-1);
        for(int i = 0;i < n;i++) if(inCycle[i]) treeDist[i] = treeDist[n];
        //for (int i = 0;i < dfs_time;i++) System.out.print(ord[i] + " ");
        //System.out.println();
        //for (int i = 0;i < n;i++) System.out.print(depth[i] + " ");
        //System.out.println();
        //System.out.println("root = " + root);
        //for(int i = 0;i < n;i++) System.out.print(treeDist[i] + " ");
        //System.out.println();
        buildRMQ();
    }
    private static void processCycle() throws Exception{
        int root = -1;
        for(int i = 0;i < n;i++) if(inCycle[i]) {
            root = i;
            first[i] = -1;
            second[i] = -1;
        }
        if(root == -1) return;
        int ctr = 0,d = 0,p = -1,t = -1;
        while (second[root] == -1){
            cycleDist[ctr] = d;
            if(first[root] == -1) first[root] = ctr;
            else second[root] = ctr;

            for(int i = 0,L = G[root].size();i < L;i++){
                int v = G[root].get(i),w = W[root].get(i);
                if(!inCycle[v] || v == p) continue;
                d += w;
                t = v;
                break;
            }
            p = root;
            root = t;
            ctr++;
        }
    }
    private static void preprocess() throws Exception{
        getCycle();
        getOuter();
        compress();
        buildTree();
        processCycle();
    }
    private static int getTreeDist(int a,int b){
        if(inCycle[a]) return 0;
        int c = lca(a,b);
        return treeDist[a] + treeDist[b] - 2*treeDist[c];
    }
    private static void answerQueries() throws Exception{
        int m = io.getNextInt();
        for(int i = 0;i < m;i++){
            int a = io.getNextInt(),b = io.getNextInt();
            int ans = 0;
            if(a == b) ;
            else if(to[a] == to[b]){
                if(inCycle[a] && inCycle[b]) throw new Exception("both in Cycle");
                if(!inCycle[a] && !inCycle[b]) ans = getTreeDist(a,b);
                else {
                    if(inCycle[b]) {int t = a;a = b; b = t;}
                    ans = getTreeDist(n,b);
                }
            }
            else{
                ans = getTreeDist(a,n) + getTreeDist(b,n);
                a = to[a]; b = to[b];
                if(first[a] > first[b]) {int t = a;a = b; b = t;}
                ans += Math.min(cycleDist[first[b]] - cycleDist[first[a]],
                            cycleDist[second[a]] - cycleDist[first[b]]);
            }
            io.println(ans);
        }
    }
    public static void main(String[] args) throws Exception{
        io = new IO(null,null);
        for(n = io.getNextInt();n != 0;n = io.getNextInt()){
            readGraph();
            preprocess();
            answerQueries();
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

