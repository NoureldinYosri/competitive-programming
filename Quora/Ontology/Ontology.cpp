#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;


struct node{
	node *left,*right;
	int count;
public:
	node():left(0),right(0),count(0){}
};


const int MAX = 100010;
int dfs_out[MAX],dfs_in[MAX],S[MAX],P[MAX],curidx[MAX];
int tdfs_out[MAX],tdfs_in[MAX],tS[MAX],tP[MAX],tcuridx[MAX];
string input[MAX],tinput[MAX];
vi data[MAX],G[MAX];
vi tdata[MAX],tG[MAX];
map<string,int> M;
int N,Q,K;
char line[MAX << 4];
int trie[MAX << 4][60];
node *ST[MAX];


void dfs(int *CurIdx,int *DFS_IN,int *DFS_OUT,int *SS,int *PP,vi *GG,vi *DATA){
	int u = 1; int dfs_time = 0;
	while(u){
		if(CurIdx[u] == 0){
			DFS_IN[u] = dfs_time;
			for(int v : DATA[u]) SS[dfs_time++] = v;
		}
		if(CurIdx[u] == sz(GG[u])){
			DFS_OUT[u] = dfs_time - 1;
			u = PP[u];
			continue;
		}
		PP[GG[u][CurIdx[u]]] = u;
		u = GG[u][CurIdx[u]++];
	}
	//cerr << dfs_time << endl;
}



void parse(){
	char *token = strtok(line," ");
	int idx = 1,l = 0;	
	for(;token;token = strtok(0," ")){
		if(token[0] == '(') {
			l = idx - 1;
		}
		else if(token[0] == ')'){
			l = P[l];
		}		
		else{
			P[idx] = l;
			G[l].pb(idx);
			M[string(token)] = idx++;
		}		
	}
}

void parse(char *s,int i){
	string name = "";
	while(*s != ':'){
		name += *s;
		s++;
	}
	s++;
	s++;
	s[strlen(s) - 1] = '\0';
	data[M[name]].pb(i);
	input[i] = string(s);
}

void insert(string & s,int id){
	int r = 1; static int size = 1;
	loop(i,len(s))	{
		char c = s[i];
		if('a' <= c && c <= 'z') c -= 'a';
		else if('A' <= c && c <= 'Z') c = c - 'A' + 26;
		else if(c == '?') c = 52;
		else c = 53; 
		
		if(!trie[r][c]) {
			trie[r][c] = ++size;
			tG[r].pb(trie[r][c]);					
		}
		r = trie[r][c];
	}
	tdata[r].pb(id);
}

node* build(int l,int r){
	node *root = new node();
	if(l == r) return root;
	int m = (l + r) >> 1;
	root->left = build(l,m);
	root->right = build(m + 1,r);
	return root;
}
node* update(node *root,int l,int r,int p){
	node *n_root = new node(); *n_root = *root; n_root->count++;	
	int m = (l + r) >> 1;
	if(l != r){
		if(p <= m) n_root->left = update(root->left,l,m,p);
		else n_root->right = update(root->right,m+1,r,p);
	}
	return n_root; 	
}
int query(node *u,node *v,int l,int r,int p){
	if(!u || !v) return 0;
	if(r <= p) return v->count - u->count;
	if(p < l) return 0;
	int m = (l + r) >> 1;
	return query(u->left,v->left,l,m,p) + query(u->right,v->right,m+1,r,p);
}

void get(int & start,int & end,string & s){
	start = (end = 0) - 1;
	int r = 1;
	loop(i,len(s)){
		char c = s[i];
		if('a' <= c && c <= 'z') c -= 'a';
		else if('A' <= c && c <= 'Z') c = c - 'A' + 26;
		else if(c == '?') c = 52;
		else c = 53; 
		if(!trie[r][c]) return;
		r = trie[r][c];
	}
	start = tdfs_in[r];
	end = tdfs_out[r];
}

int main(){
	// read tree	
	scanf("%d\n",&N);
	fgets(line,MAX << 4,stdin);
	parse();

	// read questions
	scanf("%d\n",&Q);
	loop(i,Q){
		fgets(line,MAX << 4,stdin);
		parse(line,i);
	}
	
	// preprocess
	dfs(curidx,dfs_in,dfs_out,S,P,G,data);
	// build trie
	loop(i,Q) insert(input[S[i]],i);
	dfs(tcuridx,tdfs_in,tdfs_out,tS,tP,tG,tdata);
	
	// build persistent seg-tree
	ST[0] = build(0,Q - 1);
	loop(i,Q) ST[i + 1] = update(ST[i],0,Q - 1,tS[i]);

	
	scanf("%d\n",&K);
	loop(i,K){	
		fgets(line,MAX << 4,stdin);
		string name = ""; char *s = line;
		while(*s != ' '){
			name += *s;
			s++;
		}
		s++;
		s[strlen(s) - 1] = '\0';
		string ques = string(s);
		int l = dfs_in[M[name]],r = dfs_out[M[name]],start,end;
		get(start,end,ques);
		if(r < l || end < start) puts("0");
		else{
			int ans = query(ST[start],ST[end + 1],0,Q - 1,r);
			if(l) ans -= query(ST[start],ST[end + 1],0,Q - 1,l - 1);	
			printf("%d\n",ans);
		}
	}
	return 0;
}
