#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 110000;
string P[MAX];
int trie[MAX * 10][26],n,m;
int END[MAX*10];
char password[MAX],key[MAX];

void insert(int k){
	char *p = key;
	int u = 0;
	static int ctr = 0;	
	while(*p){
		if(trie[u][*p - 'a'] == 0) trie[u][*p - 'a'] = ++ctr;
		u = trie[u][*p - 'a'];
		p++;
	}
	END[u] = k + 1;
}

int dp[10000];

int solve(int p){
	if(p == n) return m + 3;
	if(dp[p] != 0) return dp[p];
	dp[p] = -1;
	for(int u = 0,i = p;i < n;i++){
		if(trie[u][password[i] - 'a']) {
			u = trie[u][password[i] - 'a'];
			if(END[u] && solve(i + 1) != -1){
				return dp[p] = END[u];
			}
		}
		else break;
	}
	return dp[p];
}

int main(){
	scanf("%d %s %d",&n,password,&m);
	loop(i,m){
		scanf("%s",key);
		P[i] = string(key);
		int L = strlen(key);
		loop(j,L) key[j] = tolower(key[j]);
		reverse(key,key + L);
		insert(i);
	}
	solve(0);
	int p = 0;
	while(p < n){
		printf("%s",P[dp[p] - 1].c_str());
		p += len(P[dp[p] - 1]);
		if(p < n) putchar(' ');
	}
	puts("");
	return 0;
}
