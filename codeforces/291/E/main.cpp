#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 100*1000 + 10;
char buffer[MAX],P[MAX];
vi G[MAX];
int parent[MAX];
string IS[MAX];
int pf[MAX],n,m;
int memo[MAX][26];


int GetLen(char c,int l,char *s){
	int & ret = memo[l][(int)(c - 'a')];
	if(ret != -1) return ret;
	while(l && s[l] != c) l = pf[l - 1];
	if(s[l] == c) l++;
	return ret = l;
}

void BuildFailure(char *s){
	pf[0] = 0;
	int n = strlen(s);
	range(i,1,n - 1) pf[i] = GetLen(s[i],pf[i - 1],s);
}

ll dfs(int u,int len = 0) {
	ll ret = 0;
	for(char c : IS[u]){
		len = GetLen(c,len,P);
		if(len == m) {
			ret++;
			len = pf[m-1];
		}
	}
	for(int v : G[u]) ret += dfs(v,len);
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,2,n){
		scanf("%d %s",parent + i,buffer);
		G[parent[i]].pb(i);
		IS[i] = string(buffer);
	}
	scanf("%s",P);
	m = strlen(P);
	memset(memo,-1,sizeof memo);
	BuildFailure(P);
	ll ans = dfs(1);
	cout << ans << endl;
	return 0;
}
