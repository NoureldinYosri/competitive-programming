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

const int mod = 1e9 + 7,NUMBITS = 10,MAX = 1 << NUMBITS;
int cnt[MAX];
int fib[MAX];
int cA[MAX],cB[MAX],cC[MAX];
int sA[MAX],sB[MAX],sC[MAX];

int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int mul(int a,int b) {
	return (a*1LL*b)%mod;
}


void xorConv(int b,int s,int e) {
	if(b == 17) return;
	int m = (s + e) >> 1;
	xorConv(b+1,s,m);
	xorConv(b+1,m+1,e);
	for(int i = s;i <= m;i++)
		for(int j = m+1;j <= e;j++)
			cC[i^j] = add(cC[i^j],mul(cnt[i],cnt[j]));
}


void orConv(){
	cA[0] = ((cnt[0] * (cnt[0] - 1LL))/2)%mod;
	vi aux;
	for(int x = 1;x < MAX;x++) {
		loop(i,17) if((x >> i) & 1) aux.pb(i);
		for(int msk = 0;msk < (1 << sz(aux));msk++) {
			int a = 0,b = 0;
			loop(j,sz(aux))
				if((msk >> j) & 1) a |= 1 << aux[j];
				else b |= 1 << aux[j];
			assert(a != b);
			assert((a&b) == 0);
			assert((a|b) == x);
			cA[x] = add(cA[x],mul(cnt[a],cnt[b]));
		}
		sA[x] = mul(cA[x],fib[x]);
		aux.clear();
	}
}

void firstAndConv(){
	vi aux;
	for(int x = 0;x < MAX;x++) {
		loop(i,NUMBITS) if(!((x >> i) & 1)) aux.pb(i);
		for(int msk = 0;msk < (1 << sz(aux));msk++) {
			int a = x,b = x;
			loop(j,sz(aux))
				if((msk >> j) & 1) a |= 1 << aux[j];
				else b |= 1 << aux[j];
			assert((a&b) == x);
			if(x == 2 ) cerr << a << " " << b << endl;
			if(a == b) {
				assert(a == x);
				assert((x + 1) == MAX);
				cB[x] = mul(cA[x],cnt[x]);
				sB[x] = add(mul(sA[x],cnt[x]),mul(cA[x],fib[x]));
			}
			else {
				cB[x] = add(cB[x],mul(cA[a],cnt[b]));
				sB[x] = add(sB[x],mul(cnt[b],add(sA[a],mul(cA[a],fib[b]))));
			}
		}
		aux.clear();
	}


	prArr(cB,4,int);
	prArr(sB,4,int);

}
int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	fib[1] = 1;
	for(int i = 2;i < MAX;i++)
		fib[i] = add(fib[i - 1],fib[i - 2]);

	int n; scanf("%d",&n);
	loop(i,n){
		int x; scanf("%d",&x);
		cnt[x]++;
	}



	orConv();
	firstAndConv();
//
//	for(int x = 0;x < MAX;x++) {
//		ll c = cnt[x] * (cnt[x] - 1);
//		c >>= 1;
//		c %= mod;
//		cA[0] = add(cA[0],c);
//	}
//	xorConv(0,0,MAX - 1);

	return 0;
}
