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

int C[2000][2000],P[2000],W[2000],keys;
pi A[200000];

const ll mod = 1e9 + 7;

ll EXP(ll b,int p){
	b %= mod;
	if(p == 0) return 1LL;
	if(p == 1) return b;
	return (EXP(b*b,p >> 1) * EXP(b,p & 1))%mod;
}

bool cmp(const pi & u,const pi & v){
	return (u.xx == v.xx) ? (u.yy > v.yy) : (u.xx < v.xx);
}

int get(int a){
	int b = a,t;
	while(a != P[a]) a = P[a];
	while(b != P[b]){
		t = P[b];
		P[b] = a;
		b = t;
	}
	return a;
}

void join(int a,int b){
	a = get(a),b = get(b);
	if(a == b) return;
	keys --;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	P[b] = a;
}

int main(){
	int T,N,M;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&N,&M);
		keys = N;
		loop(i,N) loop(j,N) C[i][j] = 0;
		loop(i,N) P[i] = i,W[i] = 1;
		loop(i,M) scanf("%d %d",&A[i].xx,&A[i].yy),A[i].xx--,A[i].yy--;
		sort(A,A + M,&cmp);
		loop(i,M){
			int s = A[i].xx,e = A[i].yy;
			if(C[s][e]) continue;
			while(s < e) C[s++][e--] = 1;
		}
		loop(i,N) loop(j,i) if(C[j][i]) join(j,i);
		printf("%lld\n",EXP(26,keys));
	}
	return 0;
}
