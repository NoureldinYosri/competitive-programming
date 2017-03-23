#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 2000;
const int alphabet = 128;
int trie[MAX][alphabet],fail[MAX],cnt = 1;
vector<pair<char,int> > children[MAX];
vi output[MAX];
string I[MAX];
int memo[MAX][alphabet];
double dp[MAX][MAX];

void init(){
	memset(memo,-1,sizeof memo);
	memset(dp,-1,sizeof dp);
	memset(trie,0,sizeof trie);	
	loop(i,MAX) children[i].clear(),output[i].clear();
}

void insert(const char *P,int id){
	int cur = 0;
	for(const char *ptr = P;*ptr;ptr++){
		if(!trie[cur][*ptr]) {
			children[cur].pb(mp(*ptr,cnt));			
			trie[cur][*ptr] = cnt++;
		}
		cur = trie[cur][*ptr];
	}
	output[cur].pb(id);
	I[id] = string(P);
}

int get_fail(int u,int c){
	int & ret = memo[u][c];
	if(ret != -1) return ret;
	while(!trie[u][c] && u) u = trie[u][c];
	return ret = trie[u][c];
}

void BuildFailureFunction(){
	queue<int> q; 	
	fail[0] = 0;
	for(auto & e : children[0]) {
		fail[e.yy] = 0;
		q.push(e.yy);
	}
	while(!q.empty()){
		int p = q.front(); q.pop();
		for(auto & e : children[p]){
			char c = e.xx;
			int u = e.yy;
			fail[u] = get_fail(fail[p],c);
			for(int x : output[fail[u]])
				output[u].pb(x);
			sort(all(output[u]));
			output[u].resize(unique(all(output[u])) - output[u].begin());
			q.push(u);
		}
	}
}

char alpha[128];
double P[128];
int N,L;

double solve(int len,int cur){
	if(len == L) return 1;
	double & ret = dp[len][cur];
	if(ret == ret) return ret;
	ret = 0;
	loop(i,N){
		int nxt = get_fail(cur,alpha[i]);
		if(!output[nxt].empty()) continue;
		ret += P[i] * solve(len + 1,nxt);
	}
	return ret;
}

char buffer[50];

int main(){
	int T; scanf("%d",&T);
	range(t,1,T){
		init();
		int K; scanf("%d",&K);
		loop(i,K){
			scanf("%s",buffer);
			insert(buffer,i);
		}
		BuildFailureFunction();
		scanf("%d",&N);
		loop(i,N) scanf(" %c %lf",alpha + i,P + i);
		scanf("%d",&L);
		printf("Case #%d: %.15f\n",t,solve(0,0));
	//	cerr << solve(0,0) << endl;
	}	
	
	return 0;
}
