#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

#define MAXN (1 << 20)
struct cmp{
	int *R,k,n;
public:
	cmp(){}
	cmp(int a,int *b,int c):k(a),R(b),n(c){}
	bool operator () (const int & a,const int & b){
		if(k == 0) return R[a] < R[b];
		if(R[a] != R[b]) return R[a] < R[b];
		int u = min(a + k,n - 1),v = min(b + k,n - 1);
		return R[u] < R[v];
	}
};

void build(char *P,int *SA,int *R){
	int n = strlen(P);
	P[n++] = '$'; P[n] = 0;
	static int nR[MAXN];
	loop(i,n) R[i] = P[i],SA[i] = i;
	sort(SA,SA + n,cmp(0,R,n));
	for(int k = 1;k <= n;k <<= 1){
		sort(SA,SA + n,cmp(k,R,n));
		int r = 0;
		nR[SA[0]] = r;
		auto comparator = cmp(k,R,n);
		loop(i,n - 1){
			if(comparator(SA[i],SA[i + 1]) || comparator(SA[i + 1],SA[i])) r++;
			nR[SA[i + 1]] = r;  
		}
		copy(nR,nR + n,R);
	}
	//loop(i,n) cerr << R[SA[i]] << " " << (P + SA[i]) << endl;
	//cerr << endl;	
}

void computeLCP(char *T,int n,int *SA,int *LCP) {
	int i, L;
	static int Phi[MAXN],PLCP[MAXN];
	Phi[SA[0]] = -1;
	for (i = 1; i < n; i++)
		Phi[SA[i]] = SA[i-1];
	for (i = L = 0; i < n; i++) {
		if (Phi[i] == -1) { PLCP[i] = 0; continue; }
		while (i + L < n && Phi[i] + L < n && T[i + L] == T[Phi[i] + L]) L++;
		PLCP[i] = L;
		L = max(L-1, 0);
	}
	for (i = 0; i < n; i++) LCP[i] = PLCP[SA[i]];
}

char S[1 << 20],T[1 << 20];
int SA[1 << 20],R[1 << 20],LCP[1 << 20],n;

int main(){
	scanf("%d %s %s",&n,S,T);
	S[n] = '#';
	strcpy(S + n + 1,T);
	build(S,SA,R);
	computeLCP(S,2*n + 2,SA,LCP);
	int p,mx = 0;
	loop(i,2*n + 2){
		if(!i || LCP[i] <= mx) continue;
		bool c = SA[i - 1] < n && SA[i] > n;
		c |= SA[i] < n && SA[i - 1] > n;
		if(c) {
			mx = LCP[i];
			p = SA[i];
		}
	}
	loop(i,mx) putchar(S[p + i]);
	puts("");
	return 0;
}
