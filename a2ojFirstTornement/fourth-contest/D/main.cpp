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

int mul(int a,int b,int mod) {
	return (a*1LL*b)%mod;
}
int add(int a,int b,int mod) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int powmod(int a,int p,int mod){
	if(!p) return 1%mod;
	int b = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) b = mul(a,b,mod);
		a = mul(a,a,mod);
	}
	return mul(a,b,mod);
}

int n,A[1 << 20];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);
	n = unique(A,A + n) - A;
	int o ;scanf("%d",&o);
	int r = 1;
	loop(i,n)  r = mul(r,A[i]%o,o);
	r = add(r,o-1,o);
	puts(r ? "NO" : "YES");
	return 0;
}
